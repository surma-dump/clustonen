#include <cstdio>
#include <cstdlib>
#include "ClustonenModule.h"
#include "ServerSocket.h"

int main()
{
	printf ("Opening Socket...\n") ;
	ServerSocket *p ;
	try {p = new ServerSocket(22002);}
	catch (Exception e) { printf ("%s", e.getMessage().c_str()) ; exit(1) ;}
	
	printf ("Beginning to listen...\n") ;
	try { p->waitForConnection() ;}
	catch (Exception e) { printf ("%s", e.getMessage().c_str()) ; delete p ; exit(1) ;}

	printf("Other Side: %s\n", p->getOpponent().c_str()) ;
	printf("Sending Hello...\n") ;
	try { p->write("Hello!", 6) ;}
	catch (Exception e) { printf ("%s", e.getMessage().c_str()) ; delete p ;  exit(1) ;}
       
	printf("Reading...\n") ;
	int d ;
	try { d = p->read() ;}
	catch (Exception e) { printf ("%s", e.getMessage().c_str()) ; delete p ; exit(1) ;}

	printf ("Client said: \"%s\"\n", p->getMessage()) ;

	printf ("Sending Bye...\n") ;
	try{ p->write("Bye!", 4) ;}
	catch (Exception e) { printf ("%s", e.getMessage().c_str()) ; delete p ;exit(1) ;}
	p->disconnect() ;
	p->close() ;
	delete  p ;
}
