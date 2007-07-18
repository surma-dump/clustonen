#ifndef FOOCLUSTONENMODULEFOO 
#define FOOCLUSTONENMODULEFOO 

#define AUTHOR "Alexander \"crock\" Surma <crock@drebesium.org>"

#include <cstdio>
#include <cstdlib>
#include "ClustonenMessage.h"


/**
 * Abstract class to interact with modules (provided by the module itself)
 */
class ClustonenModule
{
public:
	ClustonenModule() ; // Constructor
	virtual ~ClustonenModule() ; // Destructor
		
	//TODO Module information methods
	virtual const char* getName() = 0; // returns plugin's name

	// TODO Module handling
	virtual int processMessage(ClustonenMessage* msg) = 0; // Called when a message is processed, the module is hooked for
protected:
private:
} ;

#endif
