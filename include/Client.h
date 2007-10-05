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

#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include "Socket.h"
#include "ClustonenMessage.h"
#include "ClustonenMutex.h"

class Client {
	public:
		Client(const std::string& name);
		~Client();
		
		void setName(const std::string& name);
		std::string getName();
		
		Socket* getSendSocket();
		Socket* getReceiveSocket();
		void setSendSocket(Socket* sock);
		void setReceiveSocket(Socket* sock);
		
		void sendMessage(const ClustonenMessage& msg);
		ClustonenMessage receiveMessage();
		ClustonenMessage* receiveMessagePtr();
		
	protected:
		Socket* sendSocket;
		Socket* receiveSocket;
		std::string name;
		ClustonenMutex dataMutex;
};

#endif //CLIENT_H
