#include "TestModule.h"

extern "C" const char* get_identifier() // >extern "C"< is needed to prevent symbol mangling
{
	return "testmodule-v0.0.1-beta" ; // just return the modulename
}

extern "C" ClustonenModule* get_module() // s.a.
{
	return (ClustonenModule*)new TestModule() ; // just return an initialize module
}
