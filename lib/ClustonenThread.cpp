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

/**
 * Standardconstructor
 */
ClustonenThread::ClustonenThread()
{
	threadhandler = -1 ;
}

/**
 * Destructor
 */
ClustonenThread::~ClustonenThread()
{
}

/**
 * Get the activity status of the thread
 * @Return true, if thread is running 
 */
int ClustonenThread::isRunning()
{
	return (threadhandler != 0) ;
}

/**
 * Starts the thread
 * @param param Parameter to pass on
 */
void ClustonenThread::start(void* _param) 
{
	param = _param ;
	pthread_create (&threadhandler, NULL, ClustonenThreadRun, this) ;
}

/**
 * Waits until the thread terminates and then returns
 */
void ClustonenThread::join()
{
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
	ClustonenThread *t = (ClustonenThread*)param ;
	t->run(t->getParameter()) ;
}
