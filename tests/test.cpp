#include <cstdio>
#include <cstdlib>
#include "ClustonenModule.h"
#include "ServerSocket.h"

int main()
{
	ServerSocket p(22001);
	try{p.waitForConnection() ;}
	catch (Exception e) { printf ("%s", e.getMessage().c_str()) ; }

	//try{printf("%s", p.read().c_str()) ;}
	//catch (Exception e) { printf ("%s", e.getMessage().c_str()) ; }
	try {printf("%s", p.read()) ;}
	catch (Exception e) { printf ("%s", e.getMessage().c_str()) ; }
	p.close() ;
}
