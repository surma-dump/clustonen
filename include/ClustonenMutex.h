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

#ifndef CLUSTONENMUTEX_H
#define CLUSTONENMUTEX_H

#include <pthread.h>

class ClustonenMutex {
	public:
		ClustonenMutex();
		~ClustonenMutex();
		
		int lock();
		int unlock();
		int trylock();
	
	protected:
		pthread_mutex_t mutex;
};

#endif //CLUSTONENMUTEX_H