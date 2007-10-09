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

#include "Server.h"

Server::Server(const std::string& name)
	: name(name)
{
}

/**
 * @return the server's MessageManager
 */
MessageManager& Server::getMessageManager()
{
	return mmgr;
}

/**
 * @return the server's name
 */
std::string Server::getName() {
	return name;
}

/**
 * @return the server's ModuleManager
 */
ModuleManager& Server::getModuleManager()
{
	return modmgr;
}

/**
 * Searches for a client in the list of clients.
 * @return a pointer to the client if found, else NULL.
 */
Client* Server::getClientByName(const std::string& name)
{
	clientlist_mutex.lock();
		for(std::list<Client*>::iterator it = clients.begin();
			it != clients.end();
			++it)
		{
			Client* client = (*it);
			if(client->getName() == name)
			{
				clientlist_mutex.unlock();
				return client;
				
			}
		}
	clientlist_mutex.unlock();
	
	return NULL;
}

/**
 * Adds a client to the list of clients
 * @param client the client to be added
 */
void Server::addClient(Client* client)
{
	clientlist_mutex.lock();
		clients.push_back(client);
	clientlist_mutex.unlock();
}

/**
 * Removes a client from the list of clients
 * @param client the client to be removed
 */
void Server::removeClient(Client* client)
{
	clientlist_mutex.lock();
		clients.remove(client);
	clientlist_mutex.unlock();
}
