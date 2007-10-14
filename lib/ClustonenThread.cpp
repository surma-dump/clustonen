/**
 * Copyright (C) 2007  Alexander Surma <crock@drebesium.org>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "ClustonenThread.h"
#include "Exception.h"

/**
 * Ugly structure to pass more than one argument
 * to the ClustonenThreadRun function
 */
struct run_struct {
	ClustonenThread* instance;
	bool del;
};

/**
 * Standardconstructor
 */
ClustonenThread::ClustonenThread()
	: threadhandler(-1), running(false)
{
}

/**
 * Destructor
 */
ClustonenThread::~ClustonenThread()
{
	kill();
}

/**
 * Sends a signal to the thread. Default is SIGKILL.
 * @param signal The signal to be sent.
 */
void ClustonenThread::kill(int signal)
{
	running_mutex.lock();
	
		if(!running)
			goto out;
	
		if(signal == SIGKILL)
		{
			if(pthread_cancel(threadhandler) == 0)
				running = false;
		}
		else
		{
			pthread_kill(threadhandler, signal);
		}
out:
	running_mutex.unlock();
}

/**
 * Get the activity status of the thread
 * @Return true, if thread is running 
 */
int ClustonenThread::isRunning()
{
	running_mutex.lock();
	bool tmp = running && threadhandler != -1;
	running_mutex.unlock();

	return tmp;
}

/**
 * Starts the thread
 * @param _param Parameter to pass on
 * @param deleteAfterExecution If set to true, the instance
 * will be deleted after run() has returned. NOTE: The mutex named deletionMutex
 * has to be unlocked from the outside so that the instance can be deleted.
 */
void ClustonenThread::start(void* _param, bool deleteAfterExecution) 
{
	param = _param ;
	struct run_struct* rst = new struct run_struct;
	rst->instance = this;
	rst->del = deleteAfterExecution;
	
	//Set the lock so that ClustonenThreadRun cannot
	//delete the instance before we leaved this function
	deletionMutex.lock();

	init_mutex.lock();
	
	if(pthread_create (&threadhandler, NULL, ClustonenThreadRun, rst) < 0)
		throw Exception("Could not create Thread.");

	init_mutex.lock();
	
	running_mutex.lock();
		running = true;
	running_mutex.unlock();
}

/**
 * Waits until the thread terminates and then returns
 */
void ClustonenThread::join()
{
	if(isRunning())
		pthread_join (threadhandler, NULL) ;
}

/**
 * @Return the saved parameter pointer
 */
void* ClustonenThread::getParameter()
{
	return param ;
}

/**
 * Non-Memberfunction for successful function dereferencing
 * @param t Thread to start
 * @param param Parameter to pass on
 */
void* ClustonenThreadRun(void* param)
{
	struct run_struct* rst = (struct run_struct*)param;
	ClustonenThread *t = rst->instance ;
	bool del = rst->del;

	//delete this as soon as possible (thread might be killed)
	delete rst;
	
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	
	t->init_mutex.unlock();
	t->run(t->getParameter()) ;

	t->running_mutex.lock();
		t->running = false;
	t->running_mutex.unlock();
		
	if(del)
	{
		//Wait for the creating thread to unlock
		//the mutex
		t->deletionMutex.lock();

		delete t;
	}
}
