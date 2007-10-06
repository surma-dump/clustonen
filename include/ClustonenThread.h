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

#ifndef FOOCLUSTONENTHREADFOO
#define FOOCLUSTONENTHREADFOO

#include <pthread.h>
#include "ClustonenMutex.h"

/**
 * Represents a thread and simplifies handling. Basically a C++-wrapper for pthreads.
 */
class ClustonenThread
{
public:
	ClustonenThread();
	virtual ~ClustonenThread(); 
	
	// Is thread running?
	int isRunning(); 

	// Starts the thread with given parameter
	void start(void* _param, bool deleteAfterExecution = false) ; 

	// Waits until thread terminates
	void join() ; 

	// Returns saved parameter
	void* getParameter() ; 

	// Will be run in spawned process
	virtual void run(void* _param) = 0; 
	
	/**
	 * This mutex is automatically locked by start() if deleteAfterExecution
	 * is set to true. The mutex has to be unlocked from the outside so
	 * that the instance can be deleted.
	 */
	ClustonenMutex deletionMutex;	
protected:
private:
	pthread_t threadhandler ;
	void* param ;
};

void* ClustonenThreadRun(void* param) ;
#endif
