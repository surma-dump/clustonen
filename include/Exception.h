#ifndef FOOEXCEPTIONFOO
#define FOOEXCEPTIONFOO

#define AUTHOR "Alexander \"crock\" Surma <crock@drebesium.org>"

#include <string>

class Exception
{
public:
	Exception (std::string _msg) ; // Constructor
	virtual ~Exception () ; // Destructor
		
	std::string getMessage() ; // Delivers the message of the exception
	
private:
	std::string msg ;
} ;

#endif
