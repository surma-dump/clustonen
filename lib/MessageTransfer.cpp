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

#include "MessageTransfer.h"
#include <arpa/inet.h>

/**
 * Sends a message over the socket respecting the protocol.
 * @param socket the Socket to use
 * @param message the message to send
 */
void MessageTransfer::sendMessage(Socket& socket, const ClustonenMessage& message)
{
	std::string rawMsg = message.toString();
	uint32_t length = htonl(rawMsg.length());
	
	socket.write((char*)&length, sizeof(length));
	socket.write(rawMsg.c_str(), length);
}

/**
 * Receives a message from the socket respecting the protocol.
 * @param socket the Socket to read from
 * @return The message received
 */
ClustonenMessage MessageTransfer::receiveMessage(Socket& socket)
{
	uint32_t length;
	uint32_t bytes_received;
	uint32_t buffer_size = socket.getBufferSize();
	std::string rawMsg;
	
	socket.readFixedLength(sizeof(length));
	memcpy(&length, socket.getBuffer(), sizeof(length));
	length = ntohl(length);
	
	while(bytes_received != length)
	{
		if(buffer_size < (length-bytes_received))
			bytes_received += socket.read(buffer_size);
		else
			bytes_received += socket.read(length-bytes_received);

		rawMsg += socket.getBuffer();
	}
	
	return ClustonenMessage(rawMsg);
}
