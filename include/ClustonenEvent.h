#ifndef FOOCLUSTONENEVENTFOO 
#define FOOCLUSTONENEVENTFOO 

#define AUTHOR "Alexander \"crock\" Surma <crock@drebesium.org>"

#include <cstdio> 
#include <cstdlib> 
/**
 * Abstract class representing a event
 */
class ClustonenEvent
{
	public:
		ClustonenEvent() ; // Constructor
		virtual ~ClustonenEvent() ; // Destructor
		
		//TODO Event information methods
		virtual unsigned long getTimestamp() = 0; // return the date of the occurrence

	protected:
	private:
} ;

#endif
