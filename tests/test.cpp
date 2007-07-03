#include <cstdio>
#include <cstdlib>
#include "ClustonenModule.h"
#include "ServerSocket.h"

int main()
{
	ServerSocket p(22001);
	try{p.waitForConnection() ;}
	catch (Exception e) { printf ("%s", e.getMessage().c_str()) ; p.close() ;}
	printf("Other Side: %s\n", p.getOpponent().c_str()) ;
	//try{printf("%s", p.read().c_str()) ;}
	//catch (Exception e) { printf ("%s", e.getMessage().c_str()) ; }
	int d ;
	try{d = p.read() ;}
	catch (Exception e) { printf ("%s", e.getMessage().c_str()) ; p.close() ;}
	const char* m = p.getMessage() ;
	char n[MAXLEN] ;
	memset (n, 0, MAXLEN) ;
	memcpy (n, m, d) ;
	
	n[d]='\0';
	n[d+1]='\0';
	printf("%s", n) ;
	p.close() ;
}
