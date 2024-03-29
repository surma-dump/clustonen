#include "ModuleManager.h"

/**
 * Standard constructor
 */
ModuleManager::ModuleManager()
{
	own_error = false ; // There is no error... yet...
}

/**
 * Destuctor
 */
ModuleManager::~ModuleManager()
{
	for (std::map<std::string, void*>::iterator handles=module_handles.begin(); handles != module_handles.end(); handles++) // Get every loaded plugin...
		dlclose(handles->second) ; // and close it
}

/**
 * Loads a module
 * @param filename Either a absolute path or a simple filename which is supposed to be found in $LD_LIBRARY_PATH, the folders in /etc/ld.so.cache, /lib or /usr/lib (in that order)
 * @returns an empty string if: - module could not be loaded, - identifier could not be obtained, - identifier was not unique (i.e. already used). Otherwise the identifier-string of the plugin. In an error, you should call lastError() for details
 */
std::string ModuleManager::loadModule(std::string filename)
{
	void *mod_pointer = dlopen (filename.c_str(), RTLD_LAZY) ; // try to load module

	get_identifier_func get_identifier ;
	if (mod_pointer == NULL) // if loading was not successful...
		return "" ;

	get_identifier = (get_identifier_func)dlsym (mod_pointer, "get_identifier") ; // obtain function pointer
	if (get_identifier == NULL) // if function was not found...
	{
		own_error_msg = dlerror() ; // save error message, since it will get lost after dlclose() is called
		own_error = true ; // mark, that we have our own error
		dlclose(mod_pointer) ; // close the library
		return "" ;	
	}

	module_handles[(*get_identifier)()] = mod_pointer ;
	
	return (*get_identifier)() ;
}

/**
 * Obtains a module and returns it
 * @param identifier Identifier string of the module
 * @return an instance of the module
 */
ClustonenModule* ModuleManager::getModule(std::string identifier)
{
	if (module_handles[identifier] == NULL) // Is there a module with that identifier?
	{
		own_error_msg = "No module in list with the identifier \"" + identifier + "\"\n"; // Nope! So tell that to the user!
		own_error = true ;
		return NULL ; // and return a invalid reference
	} // otherwise...
	
	get_module_func get_module = (get_module_func)dlsym (module_handles[identifier], "get_module") ; // obtain function pointer
	if (get_module == NULL) // if the function was not found
		return NULL ; // Error handling is done by libdl, so just return null
	
	return (*get_module)() ; //everything is fine, return the instance
}

/**
 * Prints last error
 * @param f File to print message to (stderr by default)
 */
void ModuleManager::lastError(FILE* f)
{
	if (own_error)
		fprintf(f, "%s\n", own_error_msg.c_str()) ;
	else
		fprintf (f, "%s\n", dlerror()) ;
	own_error = false;
}
