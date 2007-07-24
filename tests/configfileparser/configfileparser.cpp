#include <iostream>
#include <stdlib.h>
#include "ConfigFileParser.h"

#define spitoutconfigparam(x) std::cout << x << " = " << cfp->getValue(x) << std::endl

int main(int argc, char** argv)
{
	ConfigFileParser* cfp;
	
	try {
		cfp = new ConfigFileParser("./testconfiguration");
	}
	catch(ConfigFileParserException& e)
	{	
		std::cerr << "Error: " << e.getMessage() << std::endl;
		return EXIT_FAILURE;
	}
	
	spitoutconfigparam("foo");
	spitoutconfigparam("sense_of_life");
	spitoutconfigparam("linux");
	
	delete cfp;
	
	return EXIT_SUCCESS;
}
