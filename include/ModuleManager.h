#ifndef FOOMODULEMANAGERFOO
#define FOOMODULEMANAGERFOO

#define AUTHOR "Alexander \"crock\" Surma <crock@drebesium.org>"

#include <cstdio> 
#include <cstdlib> 
#include <string>
#include <dlfcn.h> // Dynamical loading of shared libraries
#include <map> 
#include "ClustonenModule.h"

//Function types to get from the library
typedef ClustonenModule* (*get_module_func)(void) ; // will return an instance of the module
typedef const char* (*get_identifier_func)(void) ; // will return an unique identifer

/**
 * Manager for loading and managing modules
 */
class ModuleManager
{
public:
	ModuleManager () ; // Constructor
	virtual	~ModuleManager() ; // Destructor
	std::string loadModule(std::string filename) ; // Tries to load a module
	void lastError (FILE* f = stderr) ;
	ClustonenModule* getModule(std::string identifier) ; // hands over a module
protected:
private:
	std::map <std::string, void*> module_handles ; // Keeps the references to the modules
	bool own_error ; // whether in intern error has occured, or dlerror() has to be called
	std::string own_error_msg ; // contains the own error message
} ;


#endif
