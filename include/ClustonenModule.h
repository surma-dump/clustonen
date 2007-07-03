#ifndef FOOCLUSTONENMODULEFOO 
#define FOOCLUSTONENMODULEFOO 

#define AUTHOR "Alexander \"crock\" Surma <crock@drebesium.org>"

#include <cstdio>
#include <cstdlib>
#include "ClustonenEvent.h"



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
	virtual int getHookPosition() = 0; // returns the desired hook to chain the module to

	// TODO Module handling
	virtual int processEvent(ClustonenEvent& event) = 0; // Called when a appropitate event hits chain
protected:
private:
} ;

enum HOOK_POSITION 
{
	MODULE_LOADING_REQUEST = 0,
	MODULE_LOADING_FINISHED	
};

enum HOOK_RETURN
{
	CHAIN_PROCEED = 0,
	CHAIN_DISMISS,
	CHAIN_STALL,
	CHAIN_RESTART
};

#endif
