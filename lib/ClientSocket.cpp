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

#include "ClientSocket.h"

/**
 * Creates a socket and connects it to a host
 * @param host Ip of the host to connect to
 * @param port Port on which to connect
 */
ClientSocket::ClientSocket(std::string host, int port) : Socket()
{
	connect(host, port) ; // connect to host
}

/**
 * Standard destructor
 */
ClientSocket::~ClientSocket()
{
	close() ; // shut everything down
}

/**
 * Connect socket to a host
 * @param host IP of the host to connect to as a string
 * @param port Port to use for the connection
 */

void ClientSocket::connect(std::string host, int port)
{
	memset(&opponentsocket, 0, sizeof (opponenthandle)) ; // Zero out struct
	opponentsocket.sin_family = AF_INET ; // TCP/IP-Socket
	opponentsocket.sin_addr.s_addr = inet_addr(host.c_str()) ; // Connecto to where?
	opponentsocket.sin_port = htons(port) ; // On which port?
	
	opponenthandle = ::connect (sockethandle, (struct sockaddr*)&opponentsocket, sizeof (opponentsocket)) ; // actually connect
	if (opponenthandle < 0) // and if it failed...
		throw Exception ("Could not connect to host. \n") ; // throw exception
	connected = true ;
	transmissionhandle = sockethandle ;
}
