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
	Socket(size_t buffer_size = SOCKET_DEFAULT_BUFFER_SIZE) ; // Constructor
	virtual ~Socket() ; // Destructor
		
	void disconnect() ; // disconnects from opponent
	void close(); // close socket

	void write(const char* msg, int len) ; // write message to connected host
	int read(size_t num_bytes, bool reset_buffer = false) ; // read incoming message

	const char* getBuffer() ; // returns saved message
	bool isConnected() ; 
	std::string getOpponent() ; // IP of the opponent
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
