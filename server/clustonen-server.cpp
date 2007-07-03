#include "clustonen-server.h"

#define AUTHOR "Alexander \"crock\" Surma <crock@drebesium.org>"

int main(int argc, char* argv[])
{
	ArgumentParser arguments (PROGNAME) ;
	arguments	<< ArgumentParser::createFlagOption(	"h","help",	"Shows this help") 
			<< ArgumentParser::createFlagOption(	"v","version",	"Shows version information") 
			<< ArgumentParser::createFlagOption(	"d","daemon",	"Start as daemon")
			<< ArgumentParser::createIntegerOption(	"p","port",	"Bind daemon to listen to this port[=23505]") ;

	int error_indicator = arguments.parse(argc, argv) ; // parse and look for unknown arguments
	if (arguments.isFlagSet("help")) // but even if there were unknown arguments, help take precedence
	{
		arguments.printUsage() ;
		exit(SUCCESS) ;
	}
	else if (arguments.isFlagSet("version")) // but even if there were unknown arguments, version take precedence if help was not set
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
		port = 23505 ; // ...use standard port
	
	
	// TODO 
	// Load Modules
	// Open Socket (Port 23505)
	// Queue
}


/**
 * Forks the server and terminates itself, so the fork runs in background like a daemon.
 */
void daemonize()
{
	pid_t pid ;
	if ((pid = fork()) < 0)
		fprintf (stderr, "%s: could not daemonize\n", PROGNAME) ;
	else if (pid)
		exit (0) ;
	chdir("/") ;
}

