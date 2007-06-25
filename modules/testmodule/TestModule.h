#ifndef FOOTESTMODULEFOO 
#define FOOTESTMODULEFOO 

#define AUTHOR "Alexander \"crock\" Surma <crock@drebesium.org>"

#include <cstdio>
#include <cstdlib>
#include "ClustonenModule.h"
#include "ClustonenEvent.h"


/**
 * Module for testing
 */
class TestModule : ClustonenModule
{
	public:
		TestModule() ; // Constructor
		virtual ~TestModule() ; // Destructor
		
		const char*	getName(); // returns plugin's name
		int		getHookPosition(); // returns the desired hook to chain the module to

		int		processEvent(ClustonenEvent& event); // Called when a appropitate event hits chain
	protected:
	private:
} ;

#endif
