#include <cstdio>
#include <cstdlib>
#include "ModuleManager.h"
#include "ClustonenModule.h"
#include "ServerSocket.h"
#include "ClientSocket.h"

int main()
{
	ServerSocket s(12121) ;
	ClientSocket p ;
	s.accept(p) ;
        std::string data ;
	
	//p << da ;
	printf("Da: %s", p.receive().c_str()) ;
// 	ModuleManager mm ;
// 	std::string ident ;
// 	if((ident = mm.loadModule ("libclustonen_testmodule.so")) == "")
// 	{
// 		mm.lastError() ;
// 		return 1 ;
// 	}
// 	else
// 		printf ("Loaded Library: %s\n", ident.c_str()) ;
// 	ClustonenModule *cm = mm.getModule(ident) ;
// 	if (cm == NULL)
// 	{
// 		mm.lastError() ;
// 		return 2 ;
// 	}
// 	printf ("Loaded Module: %s\n", cm->getName()) ;
// 	free (cm) ;
// 	return 0 ;
}
