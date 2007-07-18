#include "ArgumentParser.h"

/**
 * Standard constructor
 * @param prog_name Name of the program (for proper error messages)
 */
ArgumentParser::ArgumentParser(const char* prog_name)
{
	this->prog_name = prog_name ;
	arg_list = std::map<int, void*>::map() ;
	type_list = std::map<int, int>::map() ;
}

/**
 * Destuctor
 */
ArgumentParser::~ArgumentParser()
{
}

/**
 * Adds a flag option to the optionlist
 * @param short_desc Short name for the flag (e.g. "v" for "-v" as argument)
 * @param long_desc Long name for the flag (e.g. "version" for "--version" as argument)
 * @param full_desc Description for the parameter, printed in the help message
 */
void ArgumentParser::addFlagOption(const char* short_desc, const char* long_desc, const char* full_desc)
{
	arg_list[arg_list.size()] = arg_lit0(short_desc, long_desc, full_desc) ; //create and save flag-pointer
	type_list[type_list.size()] = ARGTYPE_FLAG ; // save type
}

/**
 * Adds a flag option to the optionlist
 * @param arg pointer to a arg_lit structure (see ArgTable2 documentation)
 */
void ArgumentParser::addFlagOption(arg_lit* arg)
{
	arg_list[arg_list.size()] = arg ; // just save the flag
	type_list[type_list.size()] = ARGTYPE_FLAG ; // save type
}

/**
 * Adds a flag option to the optionlist
 * @param short_desc Short name for the flag (e.g. "v" for "-v" as argument)
 * @param long_desc Long name for the flag (e.g. "version" for "--version" as argument)
 * @param full_desc Description for the parameter, printed in the help message
 * @return the pointer to the arg_lit struct (see Argtable2 documentation)
 */
arg_lit* ArgumentParser::createFlagOption(const char* short_desc, const char* long_desc, const char* full_desc)
{
	return arg_lit0(short_desc, long_desc, full_desc) ; // create flag with library funcion and return pointer
}

/**
 * Adds a integer option to the optionlist
 * @param short_desc Short name for the option (e.g. "v" for "-v" as argument)
 * @param long_desc Long name for the option (e.g. "version" for "--version" as argument)
 * @param full_desc Description for the parameter, printed in the help message
 */
void ArgumentParser::addIntegerOption(const char* short_desc, const char* long_desc, const char* full_desc)
{
	arg_list[arg_list.size()] = arg_int0(short_desc, long_desc, NULL, full_desc) ; //create and save option-pointer
	type_list[type_list.size()] = ARGTYPE_INTEGER ; // save type
}

/**
 * Adds a integer option to the optionlist
 * @param arg pointer to a arg_int structure (see ArgTable2 documentation)
 */
void ArgumentParser::addIntegerOption(arg_int* arg)
{
	arg_list[arg_list.size()] = arg ; // just save the option
	type_list[type_list.size()] = ARGTYPE_FLAG ; // save type
}

/**
 * Adds a integer option to the optionlist
 * @param short_desc Short name for the option (e.g. "v" for "-v" as argument)
 * @param long_desc Long name for the integer (e.g. "version" for "--version" as argument)
 * @param full_desc Description for the parameter, printed in the help message
 * @return the pointer to the arg_int struct (see Argtable2 documentation)
 */
arg_int* ArgumentParser::createIntegerOption(const char* short_desc, const char* long_desc, const char* full_desc)
{
	return arg_int0(short_desc, long_desc, NULL, full_desc) ; // create option with library funcion and return pointer
}

/**
 * The value of an integer option 
 * @param long_desc LONG description of the argument
 * @return the value of an integer options, if it is no integer or there is no option with that description, -1 is returned
 */
int ArgumentParser::getIntegerValue(const char* long_desc)
{
	for (int i = 0; i < arg_list.size(); i++) // Walk through every item...
	{
		if (strcmp(((struct arg_int*)arg_list.at(i))->hdr.longopts, long_desc) == 0) // ... and if the long description are a match
		{
			if (type_list.at(i) != ARGTYPE_INTEGER) // check whether it is NOT integer type
				return -1 ;			// and return error flag
			return ((struct arg_int*)arg_list.at(i))->ival[0] ; // if it is integer type, return its value
		}
	}
	return -2; // if there was no item found with the given description, return the error flag
}

void ArgumentParser::addEnd(int i) // Appends end mark to the optionlist
{
	if (type_list[type_list.size()-1] != ARGTYPE_END) // only if there's no end already...yay
	{
		arg_list[arg_list.size()] = arg_end(i) ; // Append end mark
		type_list[type_list.size()] = ARGTYPE_END ; // save type for continuity reasons
	}
}

void** ArgumentParser::createArgtable() 
{
// 	return arg_list.toArray() ; // sadly, this does not exist
	void** argtable = (void**)malloc(sizeof(void*)*arg_list.size()) ;// initialize array
	for (int i = 0; i < arg_list.size(); i++) // every argument pointer in the map 
		argtable[i] = arg_list.at(i) ; // is put in to a field in the array
	return argtable ; // and the array is returned, as the library function needs it
}

/**
 * Adds a flag option to the optionlist
 * @param flag flag to add
 */
ArgumentParser& ArgumentParser::operator<<(arg_lit* flag) 
{
	arg_list[arg_list.size()] = flag ; // Save flag-pointer
	type_list[type_list.size()] = ARGTYPE_FLAG ; //save type 
	return *this ;
}

/**
 * Adds a integer option to the optionlist
 * @param intopt integer option to add
 */
ArgumentParser& ArgumentParser::operator<<(arg_int* intopt)
{
	arg_list[arg_list.size()] = intopt ; // Save integer-pointer
	type_list[type_list.size()] = ARGTYPE_INTEGER ; //save type 
	return *this ;
}

/**
 * Parses the arguments with the saved argumentlist
 * @param argc Number of arguments passed
 * @param argv Array of char-pointers to the arguments themselves
 * @return see ArgTable Documentation, arg_parse(), -1 if table could not be initialized
 */
int ArgumentParser::parse(int argc, char** argv)
{
	addEnd() ;
	void** argtable = createArgtable() ; // Create array of argument structure pointers
	if (arg_nullcheck(argtable) != 0) // if argtable could not be initialized...
		return -1 ; // return

	
	int ret =  arg_parse(argc,argv,argtable); // parse with library function	
	free (argtable) ;
	return ret ;
}

/**
 * Checks whether a flag is set or not. 
 * @param long_desc LONG description of the argument
 * @return true if the flag is set, false if not or if it does not exist
 */
bool ArgumentParser::isFlagSet(const char* long_desc)
{
	for (int i = 0; i < type_list.size(); i++) // Look through typelist until ...
	{
		if (type_list.at(i) == ARGTYPE_FLAG) // ... you find a flag and ...
		{
			if(strncmp(((struct arg_lit*)arg_list.at(i))->hdr.longopts, long_desc,25) == 0) // .. check if it is the desired one and ...
				return (((struct arg_lit*)arg_list.at(i))->count>0) ; // ... return status ...
			
		} // ... or ...
	} // ... you reach the end and ...
	false ; // ... return false
}

/**
 * Prints the typical usage/help screen 
 * @param f File pointer to print msg to (stdout by default)
 */
void ArgumentParser::printUsage(FILE* f)
{
	void** argtable = createArgtable() ; // get Argtable
	fprintf (f,"Usage: %s", prog_name) ; // print program name
	arg_print_syntax(f,argtable,"\n"); // why reinvent the wheel?
	arg_print_glossary(f,argtable,"  %-25s %s\n"); // dito
}

/**
 * Generates error message out of last error (if occured) and prints it
 * @param f File pointer to print msg to (stderr by default) 
 */
void ArgumentParser::lastError(FILE* f)
{
	arg_print_errors(f, getEnd(), prog_name) ; // get Argtable and print it with library function
}

struct arg_end* ArgumentParser::getEnd()
{
	if (type_list[type_list.size()-1] == ARGTYPE_END) // check if there is an end just for security reasons
		return (struct arg_end*)arg_list[arg_list.size()-1] ;
}
