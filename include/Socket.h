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

#ifndef FOOSOCKETFOO
#define FOOSOCKETFOO

#include <arpa/inet.h>
#include <string>
#include "Exception.h"
#include "errno.h"

#define SOCKET_DEFAULT_BUFFER_SIZE 1024

class Socket
{
public:
	// Constructor
	Socket(size_t buffer_size = SOCKET_DEFAULT_BUFFER_SIZE) ;
	// Destructor
	virtual ~Socket() ;
	
	// disconnects from opponent
	void disconnect() ;
	// close socket
	void close();

	// write message to connected host
	void write(const char* msg, int len) ;
	// read incoming message
	int read(size_t num_bytes, bool reset_buffer = false) ;

	// returns saved message
	const char* getBuffer() ;
	bool isConnected() ; 
	// IP of the opponent
	std::string getOpponent() ;
	int getPort() ;
	
	size_t getBufferSize();
	size_t getNumBytesInBuffer();
	void resetBuffer();

protected:
	int sockethandle ; 
	int opponenthandle;
	int transmissionhandle ;
	struct sockaddr_in serversocket ;
	struct sockaddr_in opponentsocket;
	bool connected ;
	char* buffer ;
	size_t buffer_size;
	size_t bytes_in_buffer;

private:
} ;

#endif 
