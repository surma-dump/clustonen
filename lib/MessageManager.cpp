/**
 * Copyright (C) 2007  Alexander Surma <crock@drebesium.org>
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

#include "MessageManager.h"
#include "Server.h"
#include <algorithm>

/**
 * Standard constructor
 */
MessageManager::MessageManager(Server* srv)
	: server(srv), queue_length(0)
{
}

/**
 * Destructor
 */
MessageManager::~MessageManager()
{
}

/**
 * Adds a Hook
 * @param msgName The message type for which the module should be notified
 * @param module The module that will be notified
 */
void MessageManager::addModuleHook(const std::string& msgName, ClustonenModule* module)
{
	modulelist_mutex.lock();
		modulelist[msgName].insert(modulelist[msgName].begin(), module);
	modulelist_mutex.unlock();
}

/**
 * Removes a module's hook for a certain message type.
 * @param msgName The message type for which the module shouldn't be notified anymore
 * @param module The module whose hook should be removed
 */
void MessageManager::removeModuleHook(const std::string& msgName, ClustonenModule* module)
{
	modulelist_mutex.lock();
		modulelist[msgName].erase(find(modulelist[msgName].begin(), modulelist[msgName].end(), module));
	modulelist_mutex.unlock();
}

/**
 * Removes all Hooks that concern the specified module.
 * @param module The module whose hooks should be removed
 */
void MessageManager::removeModuleHook(ClustonenModule* module)
{
	modulelist_mutex.lock();
		for(std::map<std::string, std::list<ClustonenModule*> >::iterator it = modulelist.begin();
			it != modulelist.end();
			++it)
		{
			(it->second).erase(find((it->second).begin(), (it->second).end(), module));
		}
	modulelist_mutex.unlock();
}

/**
 * Pushes a new message into the message quere
 * @param msg New message to queue
 */
void MessageManager::queueMessage (ClustonenMessage* msg)
{
	queue_mutex.lock();
		messages.push(msg) ;
		queue_length.up();
	queue_mutex.unlock();
}

/**
 * Sends a message over the network. The message's destination
 * has to be set.
 * @param msg the message to be sent
 */
void MessageManager::sendMessage (ClustonenMessage* msg)
{
	Client* client = server->getClientByName(msg->getDestination());

	if(client == NULL)
		throw Exception("Could not deliver message to unknown client \"" + msg->getDestination() + "\"");

	client->sendMessage(*msg);
}

/**
 * Distributes the next message in line to all hooked modules.
 */
void MessageManager::distributeNext()
{
	if (messages.size() > 0)
	{
		queue_mutex.lock();
			ClustonenMessage* msg = messages.front() ;
			messages.pop() ;
		queue_mutex.unlock();

		modulelist_mutex.lock();
restart:
			std::list<ClustonenModule*> modules = modulelist[msg->getName()] ;
			for (std::list<ClustonenModule*>::iterator it = modules.begin(); it != modules.end(); ++it)
			{
				switch((*it)->processMessage(msg))
				{
					case CHAIN_STOP:
						//ugly, but efficient here
						goto out;
					
					case CHAIN_RESTART:
						//ugly, but efficient here
						goto restart;

					default:
						break;
				}
			}
out:
		modulelist_mutex.unlock();
		
		delete msg;
	}
}

/**
 * The thread's main routine that creates threads that
 * call MessageManager::distributeNext().
 * @param param A pointer to an instance of the class
 * MessageManager
 */
void MessageDistributorThread::run(void* param)
{
	MessageManager* mmgr = (MessageManager*)param;
	
	while(true)
	{
		mmgr->queue_length.down();
		DistributionCallerThread* dct = new DistributionCallerThread();
		dct->start(mmgr, true);
	}
}

/**
 * The thread's main routine that actually calls MessageManager::distributeNext().
 * @param param A pointer to an instance of the class
 * MessageManager
 */
void DistributionCallerThread::run(void* param)
{
	MessageManager* mmgr = (MessageManager*)param;
	
}
