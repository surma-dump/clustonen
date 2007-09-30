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

#include "ServerSocket.h"

/**
 * Creates a socket and binds it to a port
 * @param port Port to bind to
 */
ServerSocket::ServerSocket(int port) : Socket()
{
	// Bind it to a port
	bind(port) ;
	// and make it listen to it
	listen() ;
}

/**
 * Standard destructor
 */
ServerSocket::~ServerSocket()
{
	// shut everything down
	close() ;
}

/**
 * Binds the socket to a port
 * @param port Port to bind to
 */
void ServerSocket::bind(int port)
{
	// zero out the struct
	memset (&serversocket, 0, sizeof(serversocket)) ;
	
	// set TCP,...
	serversocket.sin_family = AF_INET;
	// No special interface (yet)
	serversocket.sin_addr.s_addr = INADDR_ANY ;
	// port
	serversocket.sin_port = htons(port) ;
	
	// Try to bind the socket to the port
	if (::bind(sockethandle, (struct sockaddr *)&serversocket, sizeof (struct sockaddr)) != 0) {
		// and throw an exception if it failed
		throw  Exception ("ClustonenLib: Could not bind to Socket. \n") ;
	}
}

/**
 * Sets the socket to listening mode
 * @param pendings Allow this number of pending connections 
 */
void ServerSocket::listen()
{
	// set it to listen
	if (::listen(sockethandle, 1) != 0) {
		// and throw an exception if it failed
		throw  Exception ("ClustonenLib: Could not switch to listening mode. \n") ;
	}
}

/**
 * Waits for an connection request and accepts it
 */
void ServerSocket::waitForConnection()
{
	socklen_t socksize = sizeof(struct sockaddr_in) ; 
	// just wait and save sockethandle of the incoming connection
	opponenthandle = ::accept(sockethandle, (struct sockaddr *) &opponentsocket, &socksize) ;
	if (opponenthandle < 0)
		throw Exception ("Could not accept connection. \n") ;
	connected = true;
	transmissionhandle = opponenthandle ;
}



