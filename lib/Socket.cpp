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

#include "Socket.h"
#include <string>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <sys/socket.h>

/**
 * Creates a socket
 * @param buffer_size The size of the receive buffer
 */
Socket::Socket(size_t buffer_size)
	: buffer_size(buffer_size), bytes_in_buffer(0),
	  transmissionhandle(-1), connected(false)
{
	// Create socket in store its handle
	sockethandle = socket(AF_INET, SOCK_STREAM, 0) ;
	
	buffer = new char[buffer_size];
	
	if(buffer == NULL)
		throw  Exception ("Socket::Socket(): Could not allocate buffer. \n") ;
}
/**
 * Creates a socket from an existing socket descriptor.
 * @param socket the socket descriptor
 * @param opponenthandle if already connected, this is the opponent handle
 * @param transmissionhandle if already connected, this is the transmission handle
 * @param
 */
Socket::Socket(int socket, struct sockaddr_in* opponent_addr, size_t buffer_size, bool connected)
	: sockethandle(socket), opponenthandle(socket),
	  transmissionhandle(socket), buffer_size(buffer_size),
	  bytes_in_buffer(0), connected(connected)
{
	buffer = new char[buffer_size];
	
	if(buffer == NULL)
		throw  Exception ("Socket::Socket(): Could not allocate buffer. \n") ;
	
	memcpy(&opponentsocket, opponent_addr, sizeof(*opponent_addr));
}

/**
 * Standard destructor
 */
Socket::~Socket()
{
	delete [] buffer;
	close() ;
}

/**
 * Closes the connection to opponent, if connected
 */
void Socket::disconnect()
{
	// if there's an actual connection
	if (isConnected())
		::close(opponenthandle) ; // close it
	connected = false ;
}

/**
 * Binds the socket to a port
 * @param port Port to bind to
 */
void Socket::bind(int port)
{
	// zero out the struct
	memset (&serversocket, 0, sizeof(serversocket)) ;
	
	// set TCP,...
	serversocket.sin_family = AF_INET;
	// No special interface (yet)
	serversocket.sin_addr.s_addr = INADDR_ANY ;
	// port
	serversocket.sin_port = htons(port) ;
	
	int opt = 1;
	if(setsockopt(sockethandle, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
		throw  Exception (strerror(errno)) ;
	} 
	
	// Try to bind the socket to the port
	if (::bind(sockethandle, (struct sockaddr *)&serversocket, sizeof (struct sockaddr)) != 0) {
		// and throw an exception if it failed
		throw  Exception (strerror(errno)) ;
	}
}

/**
 * Sets the socket to (passive) listening mode
 * @param pendings Allow this number of pending connections 
 */
void Socket::listen()
{
	// set it to listen
	if (::listen(sockethandle, 1) != 0) {
		// and throw an exception if it failed
		throw  Exception (strerror(errno)) ;
	}
}

/**
 * Waits for an connection request (if in passive mode) and accepts it
 */
void Socket::waitForConnection()
{
	socklen_t socksize = sizeof(struct sockaddr_in) ; 
	// just wait and save sockethandle of the incoming connection
	opponenthandle = ::accept(sockethandle, (struct sockaddr *) &opponentsocket, &socksize) ;
	if (opponenthandle < 0)
		throw  Exception (strerror(errno)) ;
	connected = true;
	transmissionhandle = opponenthandle ;
}

/**
 * Closes the connection, if present, and destroys socket
 */
void Socket::close()
{
	// close opponent's socket
	disconnect() ;
	// and after that yourself
	::close(sockethandle) ;
	connected = false ;
	transmissionhandle = -1 ;
}

/**
 * Connect to a host
 * @host The hosts address or name
 * @port The port number
 */
void Socket::connect(const std::string& host, unsigned int port)
{
	struct hostent *hostinfo;
	
	transmissionhandle = socket (AF_INET, SOCK_STREAM, 0);

	// get the host's address
	memset( &opponentsocket, 0, sizeof (opponentsocket));
	opponentsocket.sin_family = AF_INET;
	opponentsocket.sin_port = htons (port);
	opponentsocket.sin_addr.s_addr = inet_addr (host.c_str());
	
	if (opponentsocket.sin_addr.s_addr == INADDR_NONE) {
		//A Host name rather than an address was specified
		hostinfo = gethostbyname (host.c_str());
		memcpy((char*) &opponentsocket.sin_addr.s_addr, hostinfo->h_addr, hostinfo->h_length);
	}
	
	if(::connect(transmissionhandle, (struct sockaddr *) &opponentsocket, sizeof(struct sockaddr)) < 0)
	{
		throw  Exception (strerror(errno)) ;
	}
	
	connected = true;
}

/**
 * Sends a bytesequence to the connected host
 * @param msg bytesequence to send
 */
void Socket::write(const char* msg, int len)
{
	send_mutex.lock();
	
	// Write sequence to socket
	if (::send(transmissionhandle,msg,len,0) < 0) {
		// and throw exception if it failed
		send_mutex.unlock();
		throw  Exception (strerror(errno)) ;
	}

	send_mutex.unlock();
}

/**
 * Receives a sequence of bytes from the connected host. Note that the
 * maximum number of bytes that can be received depends on the size of
 * the buffer. The total number of bytes received in this call will be returned.
 * @param num_bytes The number of bytes to receive
 * @param reset_buffer If set to true, the buffer's content will be overwritten.
 			If set to false, the received bytes will be appended to the buffer.
 * @return Number of bytes received 
 */
ssize_t Socket::read(size_t num_bytes, bool reset_buffer)
{
	// Receive sequence and save length
	ssize_t bytes_received = ::recv(transmissionhandle,
					(reset_buffer) ? buffer : buffer + bytes_in_buffer,
					(reset_buffer)
						? ((num_bytes > buffer_size) ? buffer_size : num_bytes)
						: ((num_bytes+bytes_in_buffer > buffer_size) ? buffer_size-bytes_in_buffer : num_bytes), 0) ;
		
	// if it failed, num will be -1
	if (bytes_received < 0) {
		// and therefore an exception will be thrown
		throw  Exception (strerror(errno)) ;
	}
	
	bytes_in_buffer = (reset_buffer) ? bytes_received : bytes_in_buffer + bytes_received;
	
	return bytes_received;
}

/**
 * Receives a sequence of bytes from the connected host. The difference to
 * Socket::read() is that num_bytes specifies the minimum number of bytes
 * to receive. It cannot happen that fewer bytes are read.
 *
 * @param num_bytes The number of bytes to receive
 * @param reset_buffer If set to true, the buffer's content will be overwritten.
 			If set to false, the received bytes will be appended to the buffer.
 * @return Number of bytes received 
 */
ssize_t Socket::readFixedLength(size_t num_bytes, bool reset_buffer)
{
	if((!reset_buffer && (num_bytes > buffer_size-bytes_in_buffer)) ||
		(reset_buffer && num_bytes > buffer_size))
	{
		throw Exception("Socket::readFixedLength(): requested number of bytes doesn't fit into buffer.");
	}
	
	if(reset_buffer)
		resetBuffer();
	
	size_t bytes_read = 0;
		
	while(bytes_read < num_bytes)
		bytes_read += read(num_bytes - bytes_read, false);
	
	return bytes_read;
}

/**
 * Returns the receive-buffer's size in bytes.
 */
size_t Socket::getBufferSize()
{
	return buffer_size;
}

/**
 * Returns the number of bytes currently held in the
 * receive-buffer.
 */
size_t Socket::getNumBytesInBuffer()
{
	return bytes_in_buffer;
}

/**
 * Empties the receive-buffer
 */
void Socket::resetBuffer()
{
	memset(buffer, 0, buffer_size);
	bytes_in_buffer = 0;
}

/**
 * Returns the char array conatining sequence received in previous transmissions
 * @return previous transmissions
 */
const char* Socket::getBuffer()
{
	return buffer ;
}

/**
 * checks whether this socket is part of a connection
 * @return true if it is, false otherwise
 */
bool Socket::isConnected()
{
	// Opponenhandle is -1 if no connection is present
	return connected ;
}

/**
 * Gives IP of connected opponent
 * @return IP of connected opponent, NULL if none
 */
std::string Socket::getOpponent()
{
	if (!isConnected())
		return NULL ;
	return inet_ntoa(opponentsocket.sin_addr) ;
}
