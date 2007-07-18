#include <cstdio>
#include <cstdlib>
#include "ClustonenModule.h"
#include "ClientSocket.h"

int main()
{
	ClientSocket* p;
	printf ("Opening Socket and connecting to host...\n") ;
	try { p = new ClientSocket ("127.0.0.1", 22002);}
	catch (Exception e) { printf ("%s", e.getMessage().c_str()) ; delete p ; exit(1) ;}

	printf ("Connected: %s...\n", p->getOpponent().c_str());
	printf ("Reading...\n") ;
	try { p->read();}
	catch (Exception e) { printf ("%s", e.getMessage().c_str()) ; delete p ; exit(1) ;}
	printf("Received: \"%s\"\n", p->getMessage()) ;

	printf ("Sending answer...\n") ;
	char msg[] = "This is the client's answer!\0" ;
	try { p->write(msg, strlen(msg)) ;}
	catch (Exception e) { printf ("%s", e.getMessage().c_str()) ; delete p ; exit(1) ;}

	printf ("Reading...\n") ;
	try { p->read();}
	catch (Exception e) { printf ("%s", e.getMessage().c_str()) ; delete p ; exit(1) ;}
	printf("Received: \"%s\"\n", p->getMessage()) ;

	p->close() ;
	delete p ;
}
