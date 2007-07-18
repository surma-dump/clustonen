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

#include "MessageManager.h"

/**
 * Standard constructor
 */
MessageManager::MessageManager()
{
}

/**
 * Destructor
 */
MessageManager::~MessageManager()
{
}

/**
 * Pushes a new message into the message quere
 * @param msg New message to queue
 */
void MessageManager::queueMessage (ClustonenMessage* msg)
{
	messages.push(msg) ;
}

/**
 * Distributes the next message in line to all hooked modules.
 */
void MessageManager::distributeNext()
{
	if (messages.size() > 0)
	{
		ClustonenMessage* msg = messages.front() ;
		messages.pop() ;
		std::list<ClustonenModule*> modules = modulelist[msg->getName()] ;
		for (std::list<ClustonenModule*>::iterator module = modules.begin(); module != modules.end(); module++)
			(*module)->processMessage(msg) ;
	}
}
