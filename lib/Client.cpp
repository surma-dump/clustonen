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

Client::~Client()
{
	dataMutex.lock();
}
	
/**
 * Sets the client's name
 * @param name The client's new name
 */
void Client::setName(const std::string& name)
{
	dataMutex.lock();
		this->name = name;
	dataMutex.unlock();
}

/**
 * @return the client's name
 */
std::string Client::getName()
{
	dataMutex.lock();
		std::string tmpName = name;
	dataMutex.unlock();
	
	return tmpName;
}

/**
 * @return The socket that is used to send messages
 */
Socket* Client::getSendSocket()
{
	dataMutex.lock();
		Socket* tmpSocket = sendSocket;
	dataMutex.unlock();
	
	return tmpSocket;
}

/**
 * @return The socket that is used to receive messages
 */
Socket* Client::getReceiveSocket()
{
	dataMutex.lock();
		Socket* tmpSocket = receiveSocket;
	dataMutex.unlock();
	
	return tmpSocket;
}

/**
 * Sets the socket that is used to send messages to
 * the client.
 * @param sock The socket used to send messages
 */
void Client::setSendSocket(Socket* sock) {
	dataMutex.lock();
		sendSocket = sock;
	dataMutex.unlock();
}

/**
 * Sets the socket that is used to receive messages from
 * the client.
 * @param sock The socket used to receive messages
 */
void Client::setReceiveSocket(Socket* sock)
{
	dataMutex.lock();
		receiveSocket = sock;
	dataMutex.unlock();
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
