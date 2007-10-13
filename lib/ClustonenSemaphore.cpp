/**
 * Copyright (C) 2007  Aandi Drebes <hackbert@drebesium.org>
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

#include "ClustonenSemaphore.h"
#include "Exception.h"
#include <errno.h>

/**
 * Creates a semaphore
 * @param value The semaphore's initial value
 */
ClustonenSemaphore::ClustonenSemaphore(unsigned int value)
{
	if(sem_init(&semaphore, 0, value) < 0)
		throw Exception(strerror(errno));
}

/**
 * Destructor
 */
ClustonenSemaphore::~ClustonenSemaphore()
{
	if(sem_destroy(&semaphore) < 0)
		throw Exception(strerror(errno));
}

/**
 * Returns the semaphore's current value
 */
int ClustonenSemaphore::getValue()
{
	int value;
	
	if(sem_getvalue(&semaphore, &value) < 0)
		throw Exception(strerror(errno));

	return value;
}

/**
 * Decreases the semaphore's value by one. Acts
 * like the P() operation of a classic semaphore.
 */
void ClustonenSemaphore::down()
{
	if(sem_wait(&semaphore) < 0)
		throw Exception(strerror(errno));
}

/**
 * Tries to decrease the semaphore's value by one. If
 * the semaphore's value is currently zero, tryDown()
 * will immediately return false. If the value was
 * greater than zero, the value will be decremented by
 * one and true will be returned.
 */
bool ClustonenSemaphore::tryDown()
{
	int retval = sem_trywait(&semaphore);
	if(retval < 0) {
		if(errno == EAGAIN)
			return false;
		
		throw Exception(strerror(errno));
	}
	
	return true;
}

/**
 * Increases the semaphore's value by one. Acts
 * like the V() operation of a classic semaphore.
 */
void ClustonenSemaphore::up()
{
	if(sem_post(&semaphore) < 0)
		throw Exception(strerror(errno));
}
