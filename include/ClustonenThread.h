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
/**
 * Represents a thread and simplifies handling. Basically a C++-wrapper for pthreads.
 */
class ClustonenThread
{
public:
	ClustonenThread(); // Constructor
	virtual ~ClustonenThread() ; // Destructor
	int isRunning() ; // Is thread running?
	void start(void* _param) ; // starts the thread with given parameter
	void join() ; // waits until thread terminates
	void* getParameter() ; // Returns saved parameter
	virtual void run(void* _param) = 0; // run in spawned process
protected:
private:
	pthread_t threadhandler ;
	void* param ;
};

void* ClustonenThreadRun(void* param) ;
#endif
