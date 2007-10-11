/**
 * Copyright (C) 2007  Alexander Surma <crock@drebesium.org>
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

#include "clustonen-server.h"
#include "NetworkThread.h"
#include "MessageManager.h"
#include "ConfigFileParser.h"
#include "Server.h"
#include "config.h"
#include "Exception.h"
#include <iostream>

int main(int argc, char* argv[])
{
	ArgumentParser arguments (PROGNAME) ;
	arguments	<< arguments.createFlagOption("h","help",	"Shows this help") 
			<< arguments.createFlagOption("v","version",	"Shows version information")
			<< arguments.createStringOption("f","config-file","The configuration file")
			<< arguments.createFlagOption("d","daemon",	"Start as daemon")
			<< arguments.createIntegerOption("p","port",	"Bind daemon to listen to this port[=23505]") ;

	int error_indicator = arguments.parse(argc, argv) ; // parse and look for unknown arguments
	if (arguments.isFlagSet("help")) // but even if there were unknown arguments, help takes precedence
	{
		arguments.printUsage() ;
		exit(SUCCESS) ;
	}
	else if (arguments.isFlagSet("version")) // but even if there were unknown arguments, version takes precedence if help was not set
	{
		printf("%s version: %s\n", PROGNAME, VERSION) ;
		printf("Build: %s\n", __DATE__) ;
		exit(SUCCESS) ;
	}
	if (error_indicator != SUCCESS) // now we actually handle wrong parameters
	{
		arguments.lastError() ;
		printf("Try `%s --help' for help\n", PROGNAME) ; // just say something is wrong
		exit(ERROR_UNKNOWN_PARAMETER) ;
	}
	if (arguments.isFlagSet("daemon")) // Daemonize?
		daemonize() ; // Daemonize!
	int port = arguments.getIntegerValue("port") ; // get port number
	if(port < 0) // if there was no port specified...
		port = DEFAULT_SERVER_PORT ; // ...use standard port
	
	Server srv("ClustonenServer");
	if(arguments.getStringValue("config-file") != "")
	{
		try {
			ConfigFileParser cfp(arguments.getStringValue("config-file"));
			cfp.addMultiValueToken("module");
			cfp.parse();
			
			const std::vector<std::string> vec = cfp.getMultiValue("module");
			for(std::vector<std::string>::const_iterator it = vec.begin();
			    it != vec.end();
			    ++it)
			{
				std::string module_identifier = srv.getModuleManager().loadModule(*it);
				
				if(module_identifier == "")
					throw Exception(srv.getModuleManager().getLastError());
				
				std::cout << "Loaded module \"" << module_identifier << "\" from file \"" << *it << "\"..." << std::endl;
				
				ClustonenModule* mod = srv.getModuleManager().getModule(module_identifier, MODULE_SIDE_SERVER);
				mod->setMessageManager(&srv.getMessageManager());
			}
		} catch(Exception& e)
		{
			std::cerr << e.getMessage();
			return -1;
		}
	}
	
	NetworkThread nwThr(port, &srv);
	
	nwThr.start(NULL);
	nwThr.join();
}


/**
 * Forks the server and terminates itself, so the fork runs in background like a daemon.
 */
void daemonize()
{
	pid_t pid ;
	if ((pid = fork()) < 0) // Save ProcessID of the child and check if the fork failed
		fprintf (stderr, "%s: could not daemonize\n", PROGNAME) ; // if it did, tell us about it
	else if (pid) // if this is the motherthread
		exit (0) ; // kill it
	chdir("/") ; // the childthread changes to / for compatibility reasons
}

