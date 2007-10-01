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

#include "SocketServer.h"

/**
 * Constructor
 * @param port the TCP port number on which the server will listen
 */
SocketServer::SocketServer(unsigned int port)
	: port(port)
{
}

/**
 * Runs the main loop of the SocketServer. For each client that
 * connects, operator () is called in acceptFunc.
 * @param acceptFunc Functor that is called every time a client connects
 * @param queuelength The maximum number of clients held in a queue waiting for a connection
 * @param maxclients The maximum number of clients server (not at a time, but overall)
 */
void SocketServer::run(SocketFunctor& acceptFunc, unsigned int queuelength, int maxclients)
{
	int sock;
	int client;
	socklen_t clilen;
	int clients_accepted = 0;
	
	struct sockaddr_in serv_addr, cli_addr;

	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		throw Exception(strerror(errno));
		
	int opt = 1;
	if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
		throw  Exception (strerror(errno)) ;
	}
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(port);
	
	if (bind(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
              throw Exception(strerror(errno));
	
	listen(sock, queuelength);
	clilen = sizeof(cli_addr);
	
	while((maxclients >= 0 && (clients_accepted++) < maxclients) || (maxclients < 0))
	{
		if((client = accept(sock, (struct sockaddr *) &cli_addr, &clilen)) < 0)
			throw Exception(strerror(errno));
		
		acceptFunc(new Socket(client, SOCKET_DEFAULT_BUFFER_SIZE, client, client, true));
		close(client);
	}
	
	close(sock);
}
