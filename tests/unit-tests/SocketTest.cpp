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
#include <string.h>
#include <netdb.h>
#include "Socket.h"
#include "ClustonenThread.h"
#include "socketdefs.h"

using namespace std;

//TODO: Write more tests...

class SocketTestServerThread : public ClustonenThread
{
	protected:
		void run(void* _param)
		{
			try {
				Socket* server = (Socket*)_param;
				
				server->bind(TESTPORT);
				server->listen();
				server->waitForConnection();
				server->write(TESTMSG, strlen(TESTMSG));
			}
			catch(Exception& e)
			{
				std::cout << e.getMessage() << std::endl;
			}
		}
};

class SocketTest : public CPPUNIT_NS :: TestFixture
{
	CPPUNIT_TEST_SUITE (SocketTest);
	CPPUNIT_TEST (connectTest);
	CPPUNIT_TEST (existingHandleTest1);
	CPPUNIT_TEST (existingHandleTest2);
	CPPUNIT_TEST_SUITE_END ();
	
	public:
		void setUp (void);
		void tearDown (void);

	protected:
		void connectTest (void);
		void existingHandleTest1 (void);
		void existingHandleTest2 (void);

	private:
		Socket* server;
		Socket* client;
		Socket* client2;
};

CPPUNIT_TEST_SUITE_REGISTRATION (SocketTest);

void SocketTest::setUp(void)
{
	server = new Socket();
	client = new Socket();
}

void SocketTest::tearDown(void)
{
	delete server;
	delete client;
}


/**
 * Starts a server thread which listens for connections, then
 * connects to it, transmits a sample message and checks if it arrives
 */
void SocketTest::connectTest(void)
{
	SocketTestServerThread thrS;
	
	thrS.start(server);
	
	//FIXME: Actually, this point should be synchronized with the server thread
	//We have a lot of potential race conditions here and the test might even fail
	//because of bad timings...
	sleep(1);
	
	CPPUNIT_ASSERT(client->isConnected() == false);
	client->connect("localhost", TESTPORT);
	CPPUNIT_ASSERT(client->isConnected() == true);
	CPPUNIT_ASSERT(client->readFixedLength(strlen(TESTMSG)) == strlen(TESTMSG));
	CPPUNIT_ASSERT(memcmp(client->getBuffer(), TESTMSG, strlen(TESTMSG)) == 0);
	
	thrS.join();
}

/**
 * Creates a socket handle using socket() and allocates a new
 * instance of Socket.
 */
void SocketTest::existingHandleTest1(void)
{
	SocketTestServerThread thrS;
	
	thrS.start(server);
	
	//FIXME: Actually, this point should be synchronized with the server thread
	//We have a lot of potential race conditions here and the test might even fail
	//because of bad timings...
	sleep(1);
	
	client2 = new Socket(socket(AF_INET, SOCK_STREAM, 0));
	
	CPPUNIT_ASSERT(client2->isConnected() == false);
	client2->connect("localhost", TESTPORT);
	CPPUNIT_ASSERT(client2->isConnected() == true);
	CPPUNIT_ASSERT(client2->readFixedLength(strlen(TESTMSG)) == strlen(TESTMSG));
	CPPUNIT_ASSERT(memcmp(client2->getBuffer(), TESTMSG, strlen(TESTMSG)) == 0);
	
	thrS.join();
	
	delete client2;
}

/**
 * Creates a socket handle using socket(), connects it to a server process
 * and allocates a new instance of Socket.
 */
void SocketTest::existingHandleTest2(void)
{
	SocketTestServerThread thrS;
	
	thrS.start(server);
	
	//FIXME: Actually, this point should be synchronized with the server thread
	//We have a lot of potential race conditions here and the test might even fail
	//because of bad timings...
	sleep(1);
	
	struct sockaddr_in host_addr;
	struct hostent *hostinfo;
	
	int sock = socket (AF_INET, SOCK_STREAM, 0);

	memset( &host_addr, 0, sizeof (host_addr));
	host_addr.sin_family = AF_INET;
	host_addr.sin_port = htons (TESTPORT);
	host_addr.sin_addr.s_addr = inet_addr ("localhost");
	
	if (host_addr.sin_addr.s_addr == INADDR_NONE) {
		hostinfo = gethostbyname ("localhost");
		memcpy((char*) &host_addr.sin_addr.s_addr, hostinfo->h_addr, hostinfo->h_length);
	}
	
	if(::connect(sock, (struct sockaddr *) &host_addr, sizeof(struct sockaddr)) < 0)
		CPPUNIT_ASSERT(false);
	
	client2 = new Socket(sock, SOCKET_DEFAULT_BUFFER_SIZE, sock, sock, true);
	CPPUNIT_ASSERT(client2->isConnected() == true);
	CPPUNIT_ASSERT(client2->readFixedLength(strlen(TESTMSG)) == strlen(TESTMSG));
	CPPUNIT_ASSERT(memcmp(client2->getBuffer(), TESTMSG, strlen(TESTMSG)) == 0);
	
	thrS.join();
	
	delete client2;
}
