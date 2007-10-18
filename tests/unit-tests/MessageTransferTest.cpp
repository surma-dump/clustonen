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

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "SocketServer.h"
#include "SocketFunctor.h"
#include "ClustonenThread.h"
#include "ClustonenMutex.h"
#include "MessageTransfer.h"
#include "socketdefs.h"
#include "LockReadyFunctor.h"
#include "twofunctors.h"

using namespace std;

#define MAXCLIENTS 3

class MessageTransferTestServerThread : public ClustonenThread
{
	protected:
		void run(void* _param)
		{
			try {
				struct TwoFunctors* funcs = (TwoFunctors*)_param;
				SocketServer* server = new SocketServer(TESTPORT);
				
				server->run(*funcs->socketFunc, SOCKETSERVER_DEFAULT_QUEUELENGTH, MAXCLIENTS, funcs->readyFunc);
			}
			catch(Exception& e)
			{
				std::cout << "Server: " << e.getMessage() << std::endl;
			}
		}
};

class MessageTransferTest : public CPPUNIT_NS :: TestFixture
{
	CPPUNIT_TEST_SUITE (MessageTransferTest);
	CPPUNIT_TEST (sendReceiveTest);
	CPPUNIT_TEST_SUITE_END ();
	
	public:
		void setUp (void);
		void tearDown (void);

	protected:
		void sendReceiveTest (void);

	private:
};

class MessageWriterFunctor : public SocketFunctor
{
	public:
		void operator()(Socket* socket)
		{
			ClustonenMessage msg;
			msg.setName("aMessage");
			msg.addField("field1", "value1");
			msg.addField("field2", "value2");
			msg.addField("field3", "value3");
			
			MessageTransfer::sendMessage(*socket, msg);
			
			delete socket;
		}
};

CPPUNIT_TEST_SUITE_REGISTRATION (MessageTransferTest);

void MessageTransferTest::setUp(void)
{
}

void MessageTransferTest::tearDown(void)
{
}

/**
 * Tries to send a message over a socket and tries to receive it.
 */
void MessageTransferTest::sendReceiveTest(void)
{
	MessageTransferTestServerThread thrS;
	MessageWriterFunctor mwf;
	LockReadyFunctor rf;

	struct TwoFunctors twoFuncs;
	twoFuncs.readyFunc = &rf;
	twoFuncs.socketFunc = &mwf;
	thrS.start(&twoFuncs);
	
	rf.waitForReadyState();
	
	try {
		Socket* client = new Socket();
		client->connect("localhost", TESTPORT);
		CPPUNIT_ASSERT(client->isConnected() == true);
		
		//receive a message and check if it is correct
		ClustonenMessage msg = MessageTransfer::receiveMessage(*client);
		
		CPPUNIT_ASSERT(msg.getName() == "aMessage");
		CPPUNIT_ASSERT(msg.getField("field1") == "value1");
		CPPUNIT_ASSERT(msg.getField("field2") == "value2");
		CPPUNIT_ASSERT(msg.getField("field3") == "value3");
		
		//Do the same using a pointer
		client->connect("localhost", TESTPORT);
		ClustonenMessage* msgPtr = MessageTransfer::receiveMessagePtr(*client);
				
		CPPUNIT_ASSERT(msgPtr != NULL);
		CPPUNIT_ASSERT(msgPtr->getName() == "aMessage");
		CPPUNIT_ASSERT(msgPtr->getField("field1") == "value1");
		CPPUNIT_ASSERT(msgPtr->getField("field2") == "value2");
		CPPUNIT_ASSERT(msgPtr->getField("field3") == "value3");
		
		delete msgPtr;
		
		//and once again using receiveRawMessage
		client->connect("localhost", TESTPORT);
		msg = ClustonenMessage(MessageTransfer::receiveRawMessage(*client));
		
		CPPUNIT_ASSERT(msg.getName() == "aMessage");
		CPPUNIT_ASSERT(msg.getField("field1") == "value1");
		CPPUNIT_ASSERT(msg.getField("field2") == "value2");
		CPPUNIT_ASSERT(msg.getField("field3") == "value3");
		
		delete client;
	}
	catch(Exception& e)
	{
		std::cout << "Client: " << e.getMessage() << std::endl;
	}
	
	thrS.join();
}
