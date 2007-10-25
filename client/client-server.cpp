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

#include "client-server.h"
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <iostream>

#include "ArgumentParser.h"
#include "Socket.h"
#include "MessageTransfer.h"
#include "Server.h"
#include "ConfigFileParser.h"
#include "PluginEnvironment.h"

const char* program_name;
enum EXIT_STATUS
{
	SUCCESS = 0,
	ERROR_UNKNOWN_PARAMETER
} ;

void daemonize();

int main(int argc, char* argv[])
{
	program_name = argv[0];
	ArgumentParser arguments (program_name) ;
	arguments	<< arguments.createFlagOption("h","help",	"Shows this help") 
			<< arguments.createFlagOption("v","version",	"Shows version information")
			<< arguments.createStringOption("f","config-file","The configuration file")
			<< arguments.createFlagOption("d","daemon",	"Start as daemon")
			<< arguments.createStringOption("s","server",	"Specify the server to connect to")
			<< arguments.createIntegerOption("p","port",	"The server port to connect to") ;

	int error_indicator = arguments.parse(argc, argv) ; // parse and look for unknown arguments
	if (arguments.isFlagSet("help")) // but even if there were unknown arguments, help takes precedence
	{
		printf("HELP!\n");
		arguments.printUsage() ;
		exit(SUCCESS) ;
	}
	else if (arguments.isFlagSet("version")) // but even if there were unknown arguments, version takes precedence if help was not set
	{
		printf("%s version: %s\n", program_name, VERSION) ;
		printf("Build: %s\n", __DATE__) ;
		exit(SUCCESS) ;
	}
	if (error_indicator != SUCCESS) // now we actually handle wrong parameters
	{
		arguments.lastError() ;
		printf("Try `%s --help' for help\n", program_name) ; // just say something is wrong
		exit(ERROR_UNKNOWN_PARAMETER) ;
	}
	if (arguments.isFlagSet("daemon")) // Daemonize?
		daemonize() ; // Daemonize!
	int port = arguments.getIntegerValue("port") ; // get port number
	if(port < 0) // if there was no port specified...
		port = 23505 ; // ...use standard port
	
	std::string server = arguments.getStringValue("server");
	if(server == "")
		server = "localhost";
	
	Socket sendSocket;
	Socket receiveSocket;
	
	//The local server
	Server srv("ClustonenClient");
	PluginEnvironment pe(&srv);
	MessageDistributorThread mdt;
	mdt.start(&srv.getMessageManager());

	//The other server's name
	std::string server_name;

	if(arguments.getStringValue("config-file") != "")
	{
		try {
			ConfigFileParser cfp(arguments.getStringValue("config-file"));
			cfp.addMultiValueToken("client-module");
			cfp.addMultiValueToken("server-module");
			cfp.parse();
			
			const std::vector<std::string> client_modules = cfp.getMultiValue("client-module");
			const std::vector<std::string> server_modules = cfp.getMultiValue("server-module");

			std::map<std::string, unsigned long> modules;

			//adds all client modules to the modules map
			for(std::vector<std::string>::const_iterator it = client_modules.begin();
			    it != client_modules.end();
			    ++it)
			{
				modules[(*it)] = MODULE_SIDE_CLIENT;
			}

			//adds all server modules to the modules map
			for(std::vector<std::string>::const_iterator it = server_modules.begin();
			    it != server_modules.end();
			    ++it)
			{
				modules[(*it)] |= MODULE_SIDE_SERVER;
			}

			//Loads all modules
			for(std::map<std::string, unsigned long>::iterator it = modules.begin();
			    it != modules.end();
			    ++it)
			{
				std::string module_identifier = srv.getModuleManager().loadModule(it->first);
				
				if(module_identifier == "")
					throw Exception(srv.getModuleManager().getLastError());
				
				std::cout << "Loaded module \"" << module_identifier << "\" from file \"" << it->first << "\"..." << std::endl;

				ClustonenModule* mod;
				switch(it->second)
				{
					case MODULE_SIDE_CLIENT:
						mod = srv.getModuleManager().getModule(module_identifier, MODULE_SIDE_CLIENT, &pe);
						break;

					case MODULE_SIDE_SERVER:
						mod = srv.getModuleManager().getModule(module_identifier, MODULE_SIDE_SERVER, &pe);
						break;

					case MODULE_SIDE_SERVER | MODULE_SIDE_CLIENT:
						mod = srv.getModuleManager().getModule(module_identifier, MODULE_SIDE_CLIENT, &pe);
						mod = srv.getModuleManager().getModule(module_identifier, MODULE_SIDE_SERVER, &pe);
						break;
				}
			}
		} catch(Exception& e)
		{
			std::cerr << e.getMessage();
			return -1;
		}
	}
	
	try {
		receiveSocket.connect(server, port);
		std::cout << "Connected to server (first time)" << server << " on port " << port << std::endl;
		
		ClustonenMessage msg = MessageTransfer::receiveMessage(receiveSocket);
		if(msg.getName() != "WelcomeMessage")
			return -1;
		
		std::cout << "Received welcome message:" << std::endl;
		std::cout << "server-name: " << msg.getField("server-name") << std::endl;
		std::cout << "protocol-version: " << msg.getField("protocol-version") << std::endl;
		
		server_name = msg.getField("server-name");
		
		ClustonenMessage initRcvMsg;
		initRcvMsg.setName("InitiateTransferMessage");
		initRcvMsg.addField("connection-direction", "client-receives");
		initRcvMsg.addField("client-name", srv.getName());

		std::cout << "sending InitiateTransferMessage (client-receives)...";
		MessageTransfer::sendMessage(receiveSocket, initRcvMsg);
		std::cout << "done." << std::endl;
		
		
		sendSocket.connect(server, port);
		std::cout << std::endl << "Connected to server (second time)" << server << " on port " << port << std::endl;

		ClustonenMessage* msg2 = MessageTransfer::receiveMessagePtr(sendSocket);

		if(msg2->getName() != "WelcomeMessage") {
			delete msg2;
			return -1;
		}
		
		std::cout << "Received welcome message:" << std::endl;
		std::cout << "server-name: " << msg2->getField("server-name") << std::endl;
		std::cout << "protocol-version: " << msg2->getField("protocol-version") << std::endl;

		delete msg2;
		
		ClustonenMessage initSendMsg;
		initSendMsg.setName("InitiateTransferMessage");
		initSendMsg.addField("connection-direction", "client-sends");
		initSendMsg.addField("client-name", srv.getName());
		
		std::cout << "sending InitiateTransferMessage (client-sends)...";
		MessageTransfer::sendMessage(sendSocket, initSendMsg);
		std::cout << "done." << std::endl;

		//The server we're connected to is this local server's only client
		Client client(sendSocket.getOpponent()+"-"+server_name);
		client.setSendSocket(&sendSocket);
		client.setReceiveSocket(&receiveSocket);
		srv.addClient(&client);

		while (true)
		{
			ClustonenMessage* response;

			try {
				response = MessageTransfer::receiveMessagePtr(receiveSocket);
			}
			catch(SocketException& e)
			{
				std::cerr << "Can't receive message from " << client.getName()
					  << "... Closing connection." << std::endl;
				
				srv.removeClient(&client);
				return -1;
			}
			response->setOrigin(client.getName());
			srv.getMessageManager().queueMessage(response);
		}
	}
	catch(Exception& e) {
		std::cerr << e.getMessage() << std::endl;
		return -1;
	}
}


/**
 * Forks the server and terminates itself, so the fork runs in background like a daemon.
 * TODO: Same function exists for the master-server; put this in a library or so...
 */
void daemonize()
{
	pid_t pid ;
	if ((pid = fork()) < 0) // Save ProcessID of the child and check if the fork failed
		fprintf (stderr, "%s: could not daemonize\n", program_name) ; // if it did, tell us about it
	else if (pid) // if this is the motherthread
		exit (0) ; // kill it
	chdir("/") ; // the childthread changes to / for compatibility reasons
}

