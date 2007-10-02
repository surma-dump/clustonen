/**
 * Copyright (C) 2007  Andi Drebes <hackbert@drebesium.org>
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

#include "ClustonenMutex.h"

ClustonenMutex::ClustonenMutex()
{
	pthread_mutex_init(&mutex, NULL);
}

ClustonenMutex::~ClustonenMutex()
{
	pthread_mutex_destroy(&mutex);
}

/**
 * Locks the mutex.
 */
int ClustonenMutex::lock()
{
	return pthread_mutex_lock(&mutex);
}

/**
 * Unlocks the mutex.
 */
int ClustonenMutex::unlock()
{
	return pthread_mutex_unlock(&mutex);
}

/**
 * Tries to acquire the mutex, but doesn't queue and wait
 * if the lock is already held by another process.
 * @return true if the lock could be obtained, false otherwise
 */
int ClustonenMutex::trylock()
{
	return pthread_mutex_trylock(&mutex);
}
