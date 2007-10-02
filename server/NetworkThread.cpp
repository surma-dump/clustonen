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
#include "protocol.h"
#include <iostream>

class AcceptFunctor : public SocketFunctor
{
	public:
		void operator()(Socket* socket)
		{
			socket->write(PROTOCOL_WELCOME, PROTOCOL_WELCOME_LENGTH);
			socket->read(PROTOCOL_CLIENT_WELCOME_LENGTH);
			if(memcmp(socket->getBuffer(), PROTOCOL_CLIENT_WELCOME, PROTOCOL_CLIENT_WELCOME_LENGTH) != 0)
			{
				socket->write(PROTOCOL_ABORT, PROTOCOL_ABORT_LENGTH);
				goto out_err;
			}
			else
			{
				socket->write(PROTOCOL_ACCEPT, PROTOCOL_ACCEPT_LENGTH);
			}
		
		out_err:
			delete socket;
		}
};

AcceptFunctor acceptFunctor;

void NetworkThread::run(void* _param)
{
	try {
		SocketServer* server = new SocketServer(SERVER_PORT);
		server->run(acceptFunctor, SOCKETSERVER_DEFAULT_QUEUELENGTH, SERVER_CLIENTQUEUE_LENGTH);
	}
	catch(Exception& e)
	{
		std::cout << "Server: " << e.getMessage() << std::endl;
	}
}
