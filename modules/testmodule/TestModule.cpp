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

#include "TestModule.h"
#include "strhelper.h"
#include <iostream>
#include "ClustonenThread.h"
#include "MessageManager.h"
#include <unistd.h>
#include "Server.h"

class TestMessageSenderThread : public ClustonenThread
{
public:
	explicit TestMessageSenderThread(PluginEnvironment* pe)
		: pe(pe)
	{
	}

	void run(void* param)
	{
		MessageManager* mmgr = (MessageManager*)param;

		while(true)
		{
			try {
				ClustonenMessage m;
				m.setName("TestRequest");

				std::list<Client*> clients = pe->getServer()->getAllClients();

				if(clients.empty())
					continue;

				for(std::list<Client*>::iterator it = clients.begin();
				    it != clients.end();
				    ++it)
				{
					m.setDestination((*it)->getName());
					mmgr->sendMessage(&m);

					std::cout << "TestModule: Message sent to " << (*it)->getName() << "..." << std::endl;
				}
			}
			catch(Exception& e)
			{
				std::cerr << "TestModule: Exception: " << e.getMessage() << std::endl;
			}

			sleep(1);
		}
	}

protected:
	PluginEnvironment *pe;
};

TestModule::TestModule(PluginEnvironment *pe, bool server_mode)
	: ClustonenModule(pe), server_mode(server_mode)
{
	MessageManager* mm = &pe->getServer()->getMessageManager();
	
	if(!server_mode) {
		TestMessageSenderThread* tmst = new TestMessageSenderThread(pe);
		tmst->start(mm, true);
		mm->addModuleHook("TestReply", this);
		
		std::cout << "TestModule: started in serverclient mode..." << std::endl;
		return;
	}

	std::cout << "TestModule: started in client server mode..." << std::endl;
	mm->addModuleHook("TestRequest", this);
}

/**
 * Destructor
 */
TestModule::~TestModule()
{
}

std::string TestModule::getName()
{
	return "TestModule" ;
}

int TestModule::processMessage (ClustonenMessage* msg)
{
	if(!server_mode)
	{
		if (msg->getName() != "TestReply") 
			return CHAIN_PROCEED;

		std::cout << "TestModule: received TestReply from client " << msg->getOrigin() << " with original-address: "
			  << msg->getField("original-address") << std::endl;
		return CHAIN_STOP ;
	}
	else
	{
		if (msg->getName() != "TestRequest") 
			return CHAIN_PROCEED;

		std::cout << "TestModule: received TestRequest from client " << msg->getOrigin() << std::endl;
	
		ClustonenMessage ret;
		ret.setName("TestReply");
		ret.addField("original-address", numberToString((unsigned long)msg));
		ret.setDestination(msg->getOrigin());

		try {
			pe->getServer()->getMessageManager().sendMessage(&ret);
		}
		catch(Exception& e)
		{
			std::cerr << "TestModule: Exception: " << e.getMessage() << std::endl;
		}
		
		return CHAIN_STOP ;
	}
}
