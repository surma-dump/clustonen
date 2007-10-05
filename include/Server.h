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

#ifndef SERVER_H
#define SERVER_H

#include <string>
#include "MessageManager.h"
#include "Client.h"
#include "ClustonenMutex.h"

class Server {
	public:
		Server(const std::string& name);
		
		std::string getName();
		MessageManager& getMessageManager();
		Client* getClientByName(const std::string& name);
		void addClient(Client* client);
		void removeClient(Client* client);
		
	protected:
		std::string name;
		MessageManager mmgr;
		std::list<Client*> clients;
		ClustonenMutex clientlist_mutex;
};

#endif //SERVER_H
