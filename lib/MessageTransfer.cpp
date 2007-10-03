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
 */
void MessageTransfer::sendMessage(Socket& socket, const ClustonenMessage& message)
{
	std::string rawMsg = message.getData();
	uint32_t length = rawMsg.length();
	
	socket.write((char*)&length, sizeof(length));
	socket.write(rawMsg.c_str(), length);
}
