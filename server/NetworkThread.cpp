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
		AcceptFunctor(Server* srv)
			: srv(srv)
		{
		}
		
		void operator()(Socket* socket)
		{
			ClientHandlerThread* cht = new ClientHandlerThread(srv);
			cht->start(socket, true);
			cht->deletionMutex.unlock();
		}
	
	protected:
		Server* srv;
};

//////////////////////////////////////////////////////////////////////////////////

ClientHandlerThread::ClientHandlerThread(Server* srv)
	: srv(srv)
{
}

void ClientHandlerThread::run(void* _param)
{
	Socket* socket = (Socket*)_param;
	Client* client;
	std::string client_name;
	
	try {
		WelcomeMessage welcome;
		ClustonenMessage* response;
		
		MessageTransfer::sendMessage(*socket, welcome);
		
		response = MessageTransfer::receiveMessagePtr(*socket);
		client_name = socket->getOpponent()+"-"+response->getField("client-name");
		
		if(response->getName() != "InitiateTransferMessage")
		{
			socket->disconnect();
			delete socket;
			delete response;
			return;
		}
		
		if(response->getField("connection-direction") == "client-receives")
		{
			client = new Client(client_name);
			client->setSendSocket(socket);
			srv->addClient(client);
			
			std::cout << "Added client " << client->getName() << "..." << std::endl;
			
			delete response;
			return;
			
		}
		else if(response->getField("connection-direction") == "client-sends")
		{
			client = srv->getClientByName(client_name);
			if(client == NULL)
			{
				socket->disconnect();
				delete socket;
				delete response;
				return;
			}
			
			client->setReceiveSocket(socket);
			std::cout << "Two-way connection to " << client->getName() << " established..." << std::endl;
		}
		delete response;
		
		while(true)
		{
			response = MessageTransfer::receiveMessagePtr(*socket);
			response->setOrigin(client_name);
			if(response->getName() == "AbortMessage")
			{
				srv->getMessageManager().queueMessage(response);
				srv->removeClient(client);
				socket->disconnect();
				delete client->getSendSocket();
				delete client->getReceiveSocket();
				delete client;
				return;
			}
			
			srv->getMessageManager().queueMessage(response);
		}
	}
	catch(Exception& e)
	{
		std::cout << e.getMessage() << std::endl;
	}
			
	delete socket;
}

//////////////////////////////////////////////////////////////////////////////////

NetworkThread::NetworkThread(unsigned int port, Server* srv)
	: port(port), srv(srv)
{
}

void NetworkThread::run(void* _param)
{
	try {
		AcceptFunctor acceptFunctor(srv);
		
		SocketServer* sock_server = new SocketServer(port);
		sock_server->run(acceptFunctor, SOCKETSERVER_DEFAULT_QUEUELENGTH, SERVER_CLIENTQUEUE_LENGTH);
	}
	catch(Exception& e)
	{
		std::cout << "Server: " << e.getMessage() << std::endl;
	}
}
