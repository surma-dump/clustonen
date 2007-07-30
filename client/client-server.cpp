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

#include "ArgumentParser.h"
#include "ServerSocket.h"

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

