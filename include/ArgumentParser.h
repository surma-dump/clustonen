/**
 * Copyright (C) 2007  Alexander Surma <crock@drebesium.org>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef FOOARGUMENTPARSERFOO
#define FOOARGUMENTPARSERFOO

#define AUTHOR "Alexander \"crock\" Surma <crock@drebesium.org>"

#include <cstdio> 
#include <cstdlib> 
#include <string>
#include <argtable2.h> // Library headers
#include <map> // map
#include <vector>

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
	ArgumentParser(const std::string& prog_name) ; // Constructor
	virtual	~ArgumentParser() ; // Destructor

	void addFlagOption(const std::string&  short_desc, const std::string&  long_desc, const std::string&  full_desc) ; // adds a flag
	void addFlagOption(arg_lit* arg) ; // adds a flag  
	ArgumentParser&	operator<<(arg_lit* flag) ; // "Append"-Operator for flags

	void addIntegerOption(const std::string&  short_desc, const std::string&  long_desc, const std::string&  full_desc) ;
	void addIntegerOption(arg_int* arg) ;
	ArgumentParser&	operator<<(arg_int* flag) ;
	int getIntegerValue (const std::string&  long_desc) ;
	
	void addStringOption(const std::string&  short_desc, const std::string&  long_desc, const std::string&  full_desc) ;
	void addStringOption(arg_str* arg) ;
	ArgumentParser&	operator<<(arg_str* flag) ;
	std::string getStringValue (const std::string&  long_desc) ;

	int parse(int argc, char** argv) ; // parses arguments, maybe even output
	bool isFlagSet(const std::string&  long_desc) ; // checks whether a flag is set
	void printUsage(FILE* f = stdout) ; // generates typical helpscreen
	void lastError(FILE* f = stderr) ; // generate errormsg with last error

	arg_lit* createFlagOption(const std::string&  short_desc, const std::string&  long_desc, const std::string&  full_desc) ; // Creates a flag (for usage with << operator)
	arg_int* createIntegerOption(const std::string&  short_desc, const std::string&  long_desc, const std::string&  full_desc) ; // Creates a option which takes in integer (for usage with << operator)
	arg_str* createStringOption(const std::string&  short_desc, const std::string&  long_desc, const std::string&  full_desc) ;

protected:
private:
	void addEnd(int = 20) ; //adds end to the option list
	void** createArgtable() ; // creates an array from the arg vektor
	struct arg_end* getEnd() ; // get the end option
	std::string  prog_name ; // program name
	std::map <int, void*> arg_list ; //Contains map index=>argument struct pointer
	std::map <int, int> type_list ; //Contains map index=>ARGTYPE (for typecast when reading)
	std::vector<char*> c_buffers; //Contains all buffers allocated with copystr
} ;

#endif
