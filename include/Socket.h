/**
 * Copyright (C) 2007  Alexander Surma <crock@drebesium.org>
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
	
	Socket(int socket, struct sockaddr_in* opponent_addr,
		size_t buffer_size = SOCKET_DEFAULT_BUFFER_SIZE, bool connected = false) ;
	
	// Destructor
	virtual ~Socket() ;
	
	// disconnects from opponent
	void disconnect() ;
	
	void connect(const std::string& host, unsigned int port);
	
	// close socket
	void close();

	// write message to connected host
	void write(const char* msg, int len) ;
	// read incoming message
	ssize_t read(size_t num_bytes, bool reset_buffer = true) ;
	ssize_t readFixedLength(size_t num_bytes, bool reset_buffer = true) ;

	// returns saved message
	const char* getBuffer() ;
	bool isConnected() ; 
	// IP of the opponent
	std::string getOpponent() ;
	int getPort() ;
	
	// Returns size of buffer for messages
	size_t getBufferSize();
	// Returns how many bytes are actually used by a message
	size_t getNumBytesInBuffer();
	// Resets the buffer
	void resetBuffer();
	
	// Binds socket to a port
	void bind(int port);
	// Makes it a (passive) listening socket. 
	void listen();
	// Waits for an incoming connection
	void waitForConnection();

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
