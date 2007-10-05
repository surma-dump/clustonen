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

#include "Client.h"
#include "MessageTransfer.h"

Client::Client(const std::string& name)
	: name(name), sendSocket(NULL), receiveSocket(NULL)
{
}
	
/**
 * Sets the client's name
 * @param name The client's new name
 */
void Client::setName(const std::string& name) {
	this->name = name;
}

/**
 * @return the client's name
 */
std::string Client::getName() {
	return name;
}

/**
 * @return The socket that is used to send messages
 */
Socket* Client::getSendSocket() {
	return sendSocket;
}

/**
 * @return The socket that is used to receive messages
 */
Socket* Client::getReceiveSocket() {
	return receiveSocket;
}

/**
 * Sets the socket that is used to send messages to
 * the client.
 * @param sock The socket used to send messages
 */
void Client::setSendSocket(Socket* sock) {
	sendSocket = sock;
}

/**
 * Sets the socket that is used to receive messages from
 * the client.
 * @param sock The socket used to receive messages
 */
void Client::SetReceiveSocket(Socket* sock) {
	receiveSocket = sock;
}

void Client::sendMessage(const ClustonenMessage& msg) {
	MessageTransfer::sendMessage(*sendSocket, msg);
}

ClustonenMessage Client::receiveMessage() {
	return MessageTransfer::receiveMessage(*receiveSocket);
}

ClustonenMessage* Client::receiveMessagePtr() {
	return MessageTransfer::receiveMessagePtr(*receiveSocket);
}
