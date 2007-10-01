 
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
#include "socketdefs.h"

using namespace std;

#define MAXCLIENTS 10

class SocketServerTestServerThread : public ClustonenThread
{
	protected:
		void run(void* _param)
		{
			try {
				SocketFunctor* func = (SocketFunctor*)_param;
				SocketServer* server = new SocketServer(TESTPORT);
				
				server->run(*func, SOCKETSERVER_DEFAULT_QUEUELENGTH, MAXCLIENTS);
			}
			catch(Exception& e)
			{
				std::cout << "Server: " << e.getMessage() << std::endl;
			}
		}
};

class SocketServerTest : public CPPUNIT_NS :: TestFixture
{
	CPPUNIT_TEST_SUITE (SocketServerTest);
	CPPUNIT_TEST (connectTest);
	CPPUNIT_TEST_SUITE_END ();
	
	public:
		void setUp (void);
		void tearDown (void);

	protected:
		void connectTest (void);

	private:
};

class SocketFunctorSample : public SocketFunctor
{
	public:
		void operator()(Socket* socket)
		{
			socket->write(TESTMSG, strlen(TESTMSG));
			delete socket;
		}
};

CPPUNIT_TEST_SUITE_REGISTRATION (SocketServerTest);

void SocketServerTest::setUp(void)
{
}

void SocketServerTest::tearDown(void)
{
}


void SocketServerTest::connectTest(void)
{
	SocketServerTestServerThread thrS;
	SocketFunctorSample* func = new SocketFunctorSample();
	
	thrS.start(func);
	
	//FIXME: Actually, this point should be synchronized with the server thread
	//We have a lot of potential race conditions here and the test might even fail
	//because of bad timings...
	sleep(1);
	
	for(int i = 0; i < MAXCLIENTS; ++i)
	{
		try {
			Socket* client = new Socket();
			client->connect("localhost", TESTPORT);
			CPPUNIT_ASSERT(client->isConnected() == true);
			CPPUNIT_ASSERT(client->read(strlen(TESTMSG)) == strlen(TESTMSG));
			CPPUNIT_ASSERT(memcmp(client->getBuffer(), TESTMSG, strlen(TESTMSG)) == 0);
			delete client;
		}
		catch(Exception& e)
		{
			std::cout << "Client: " << e.getMessage() << std::endl;
		}
	}
	
	thrS.join();
	
	delete func;
}
