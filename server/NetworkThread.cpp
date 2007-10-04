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

#include "NetworkThread.h"
#include "SocketFunctor.h"
#include "ClustonenThread.h"
#include "SocketServer.h"
#include "config.h"
#include "WelcomeMessage.h"
#include "MessageTransfer.h"
#include <iostream>

class AcceptFunctor : public SocketFunctor
{
	public:
		AcceptFunctor(MessageManager* mmgr)
			: mmgr(mmgr)
		{
		}
		
		void operator()(Socket* socket)
		{
			ClientHandlerThread* cht = new ClientHandlerThread(mmgr);
			cht->start(socket, true);
			cht->deletionMutex.unlock();
		}
	
	protected:
		MessageManager* mmgr;
};

//////////////////////////////////////////////////////////////////////////////////

ClientHandlerThread::ClientHandlerThread(MessageManager* mmgr)
	: mmgr(mmgr)
{
}

void ClientHandlerThread::run(void* _param)
{
	Socket* socket = (Socket*)_param;
	
	try {
		WelcomeMessage welcome;
		ClustonenMessage* response;
				
		MessageTransfer::sendMessage(*socket, welcome);
		
		response = MessageTransfer::receiveMessagePtr(*socket);
		if(response->getName() != "AcceptMessage")
		{
			socket->disconnect();
			delete socket;
			delete response;
			return;
		}
		delete response;
		
		while(true)
		{
			response = MessageTransfer::receiveMessagePtr(*socket);
			if(response->getName() == "AbortMessage")
			{
				mmgr->queueMessage(response);
				socket->disconnect();
				delete socket;
				return;
			}
			
			mmgr->queueMessage(response);
		}
	}
	catch(Exception& e)
	{
		std::cout << e.getMessage() << std::endl;
	}
			
	delete socket;
}

//////////////////////////////////////////////////////////////////////////////////

NetworkThread::NetworkThread(unsigned int port, MessageManager* mmgr)
	: port(port), mmgr(mmgr)
{
}

void NetworkThread::run(void* _param)
{
	try {
		AcceptFunctor acceptFunctor(mmgr);
		
		SocketServer* server = new SocketServer(port);
		server->run(acceptFunctor, SOCKETSERVER_DEFAULT_QUEUELENGTH, SERVER_CLIENTQUEUE_LENGTH);
	}
	catch(Exception& e)
	{
		std::cout << "Server: " << e.getMessage() << std::endl;
	}
}
