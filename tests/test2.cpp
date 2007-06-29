#include <cstdio>
#include <cstdlib>
#include "ModuleManager.h"
#include "ClustonenModule.h"
#include "Socket.h"

int main()
{
	Socket p = Socket() ;
	try {p.connect ("127.0.0.1", 22000) ;}
	catch (Exception e) { printf ("%s", e.getMessage().c_str()) ; }
	try {p.write ("Neger!\0") ;}
	catch (Exception e) { printf ("%s", e.getMessage().c_str()) ; }
	try{p.close() ;}
	catch (Exception e) { printf ("%s", e.getMessage().c_str()) ; }
}
