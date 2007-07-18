#ifndef FOOARGUMENTPARSERFOO
#define FOOARGUMENTPARSERFOO

#define AUTHOR "Alexander \"crock\" Surma <crock@drebesium.org>"

#include <cstdio> 
#include <cstdlib> 
#include <argtable2.h> // Library headers
#include <map> // map

enum ARGTYPES
{
	ARGTYPE_FLAG = 0,
	ARGTYPE_STRING,
	ARGTYPE_INTEGER,
	ARGTYPE_REAL,
	ARGTYPE_FILE,
	ARGTYPE_END
} ;

/**
 * Wrapper class for the ArgTable 2 Library
 */
class ArgumentParser
{
public:
	ArgumentParser(const char* prog_name) ; // Constructor
	virtual	~ArgumentParser() ; // Destructor

	void addFlagOption(const char* short_desc, const char* long_desc, const char* full_desc) ; // adds a flag
	void addFlagOption(arg_lit* arg) ; // adds a flag  
	ArgumentParser&	operator<<(arg_lit* flag) ; // "Append"-Operator for flags

	void addIntegerOption(const char* short_desc, const char* long_desc, const char* full_desc) ; // adds a flag
	void addIntegerOption(arg_int* arg) ; // adds a flag  
	ArgumentParser&	operator<<(arg_int* flag) ; // "Append"-Operator for flags
	int getIntegerValue (const char* long_desc) ;

	int parse(int argc, char** argv) ; // parses arguments, maybe even output
	bool isFlagSet(const char* long_desc) ; // checks whether a flag is set
	void printUsage(FILE* f = stdout) ; // generates typical helpscreen
	void lastError(FILE* f = stderr) ; // generate errormsg with last error

	//Statics
	static arg_lit* createFlagOption(const char* short_desc, const char* long_desc, const char* full_desc) ; // Creates a flag (for usage with << operator)
	static arg_int* createIntegerOption(const char* short_desc, const char* long_desc, const char* full_desc) ; // Creates a option which takes in integer (for usage with << operator)

protected:
private:
	void addEnd(int = 20) ; //adds end to the option list
	void** createArgtable() ; // creates an array from the arg vektor
	struct arg_end* getEnd() ; // get the end option
	const char* prog_name ; // program name
	std::map <int, void*> arg_list ; //Contains map index=>argument struct pointer
	std::map <int, int> type_list ; //Contains map index=>ARGTYPE (for typecast when reading)
} ;

#endif
