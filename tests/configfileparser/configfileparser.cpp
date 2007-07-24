#include <iostream>
#include <stdlib.h>
#include "ConfigFileParser.h"

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
	
	std::cout << "Number of entries found in configfile: " << cfp->getNumValues() << std::endl;
	std::map<std::string,std::string> vals = cfp->getValues();
	for(std::map<std::string,std::string>::iterator iter = vals.begin();
		iter != vals.end();
		++iter)
	{
		std::cout << "\"" << iter->first << "\" = \"" << iter->second << "\"" << std::endl;
	}
	
	delete cfp;
	
	return EXIT_SUCCESS;
}
