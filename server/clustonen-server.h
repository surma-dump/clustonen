#ifndef FOOCLUSTONENSERVERFOO
#define FOOCLUSTONENSERVERFOO

#define AUTHOR "Alexander \"crock\" Surma <crock@drebesium.org>"
#define PROGNAME "clustonen-server"
#define VERSION "0.0.1"

#include <cstdio> // Basic I/O
#include <cstdlib> // pid_t
#include <unistd.h> // fork()
#include <argtable2.h> // argument parsing library


#include "ArgumentParser.h"

//#include <sys/types.h>


int main(int argc, char** argv) ; // Main Function
void daemonize() ; // Bring server to background

enum EXIT_STATUS
{
	SUCCESS = 0,
	ERROR_UNKNOWN_PARAMETER
} ;

#endif
