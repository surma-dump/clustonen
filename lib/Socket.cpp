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

#include "Socket.h"

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
		throw  Exception ("ClustonenLib: Could not allocate buffer. \n") ;
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
 * Sends a bytesequence to the connected host
 * @param msg bytesequence to send
 */
void Socket::write(const char* msg, int len)
{
	// Write sequence to socket
	if (::send(transmissionhandle,msg,len,0) < 0) {
		// and throw exception if it failed
		throw  Exception ("ClustonenLib: Could not send string. \n") ;
	}
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
int Socket::read(size_t num_bytes, bool reset_buffer)
{
	// Receive sequence and save length
	ssize_t bytes_received = ::recv(transmissionhandle,
					(reset_buffer) ? buffer : buffer + bytes_in_buffer,
					num_bytes, 0) ;
		
	// if it failed, num will be -1
	if (bytes_received < 0) {
		// and therefore an exception will be thrown
		throw Exception ("ClustonenLib: Could not receive byte sequence. \n") ;
	}
	
	bytes_in_buffer = (reset_buffer) ? bytes_received : bytes_in_buffer + bytes_received;
	
	return bytes_received;
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
