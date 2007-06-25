#include <cstdio>
#include <cstdlib>
#include "ModuleManager.h"
#include "ClustonenModule.h"
#include "Socket.h"

int main()
{
	Socket p;
	Socket c;
	try{p.bind(22000) ;}
	catch (Exception e) { printf ("%s", e.getMessage().c_str()) ; }
	try{p.listen() ;}
	catch (Exception e) { printf ("%s", e.getMessage().c_str()) ; }
	try{c = p.accept() ;}
	catch (Exception e) { printf ("%s", e.getMessage().c_str()) ; }
	try{printf("%s", p.read().c_str()) ;}
	catch (Exception e) { printf ("%s", e.getMessage().c_str()) ; }
	c.close() ;
	p.close() ;
}
