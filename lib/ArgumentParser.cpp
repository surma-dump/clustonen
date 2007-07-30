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

#include "ArgumentParser.h"
#include "strhelper.h"

/**
 * Standard constructor
 * @param prog_name Name of the program (for proper error messages)
 */
ArgumentParser::ArgumentParser(const std::string& prog_name)
{
	this->prog_name = prog_name;
}

/**
 * Destuctor
 */
ArgumentParser::~ArgumentParser()
{
	//create temporary argtable
	void** argtable = createArgtable() ;
	
	//Free the argtable structures
	arg_freetable(argtable, arg_list.size());
	
	//delete the temporary argtable
	delete [] argtable;
	
	//delete all c-buffers
	for(std::vector<char*>::iterator it = c_buffers.begin();
		it != c_buffers.end();
		++it)
	{
		delete [] (*it);
	}
}

/**
 * Adds a flag option to the optionlist
 * @param short_desc Short name for the flag (e.g. "v" for "-v" as argument)
 * @param long_desc Long name for the flag (e.g. "version" for "--version" as argument)
 * @param full_desc Description for the parameter, printed in the help message
 */
void ArgumentParser::addFlagOption(const std::string&  short_desc, const std::string&  long_desc, const std::string&  full_desc)
{
	char* short_desc_c = copystr(short_desc);
	char* long_desc_c = copystr(long_desc);
	char* full_desc_c = copystr(full_desc);
	c_buffers.push_back(short_desc_c);
	c_buffers.push_back(long_desc_c);
	c_buffers.push_back(full_desc_c);
	
	arg_list[arg_list.size()] = arg_lit0(short_desc_c, long_desc_c, full_desc_c) ; //create and save flag-pointer
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
arg_lit* ArgumentParser::createFlagOption(const std::string&  short_desc, const std::string&  long_desc, const std::string&  full_desc)
{
	char* short_desc_c = copystr(short_desc);
	char* long_desc_c = copystr(long_desc);
	char* full_desc_c = copystr(full_desc);
	c_buffers.push_back(short_desc_c);
	c_buffers.push_back(long_desc_c);
	c_buffers.push_back(full_desc_c);
	return arg_lit0(short_desc_c, long_desc_c, full_desc_c) ; // create flag with library funcion and return pointer
}

/**
 * Adds a integer option to the optionlist
 * @param short_desc Short name for the option (e.g. "v" for "-v" as argument)
 * @param long_desc Long name for the option (e.g. "version" for "--version" as argument)
 * @param full_desc Description for the parameter, printed in the help message
 */
void ArgumentParser::addIntegerOption(const std::string&  short_desc, const std::string&  long_desc, const std::string&  full_desc)
{
	char* short_desc_c = copystr(short_desc);
	char* long_desc_c = copystr(long_desc);
	char* full_desc_c = copystr(full_desc);
	c_buffers.push_back(short_desc_c);
	c_buffers.push_back(long_desc_c);
	c_buffers.push_back(full_desc_c);
	
	arg_list[arg_list.size()] = arg_int0(short_desc_c, long_desc_c, NULL, full_desc_c) ; //create and save option-pointer
	type_list[type_list.size()] = ARGTYPE_INTEGER ; // save type
}

/**
 * Adds a integer option to the optionlist
 * @param arg pointer to a arg_int structure (see ArgTable2 documentation)
 */
void ArgumentParser::addIntegerOption(arg_int* arg)
{
	arg_list[arg_list.size()] = arg ; // just save the option
	type_list[type_list.size()] = ARGTYPE_INTEGER ; // save type
}

/**
 * Adds a integer option to the optionlist
 * @param short_desc Short name for the option (e.g. "v" for "-v" as argument)
 * @param long_desc Long name for the integer (e.g. "version" for "--version" as argument)
 * @param full_desc Description for the parameter, printed in the help message
 * @return the pointer to the arg_int struct (see Argtable2 documentation)
 */
arg_int* ArgumentParser::createIntegerOption(const std::string&  short_desc, const std::string&  long_desc, const std::string&  full_desc)
{
	char* short_desc_c = copystr(short_desc);
	char* long_desc_c = copystr(long_desc);
	char* full_desc_c = copystr(full_desc);
	c_buffers.push_back(short_desc_c);
	c_buffers.push_back(long_desc_c);
	c_buffers.push_back(full_desc_c);
	
	return arg_int0(short_desc_c, long_desc_c, NULL, full_desc_c) ; // create option with library funcion and return pointer
}

/**
 * The value of an integer option 
 * @param long_desc LONG description of the argument
 * @return the value of an integer options, if it is no integer or there is no option with that description, -1 is returned
 */
int ArgumentParser::getIntegerValue(const std::string&  long_desc)
{
	for (int i = 0; i < arg_list.size(); i++) // Walk through every item...
	{
		if (strcmp(((struct arg_int*)arg_list.at(i))->hdr.longopts, long_desc.c_str()) == 0) // ... and if the long description are a match
		{
			if (type_list.at(i) != ARGTYPE_INTEGER) // check whether it is NOT integer type
				return -1 ;			// and return error flag
			return ((struct arg_int*)arg_list.at(i))->ival[0] ; // if it is integer type, return its value
		}
	}
	return -2; // if there was no item found with the given description, return the error flag
}

/**
 * Adds a string option to the optionlist
 * @param short_desc Short name for the option (e.g. "v" for "-v" as argument)
 * @param long_desc Long name for the option (e.g. "version" for "--version" as argument)
 * @param full_desc Description for the parameter, printed in the help message
 */
void ArgumentParser::addStringOption(const std::string&  short_desc, const std::string&  long_desc, const std::string&  full_desc)
{
	char* short_desc_c = copystr(short_desc);
	char* long_desc_c = copystr(long_desc);
	char* full_desc_c = copystr(full_desc);
	c_buffers.push_back(short_desc_c);
	c_buffers.push_back(long_desc_c);
	c_buffers.push_back(full_desc_c);
	
	arg_list[arg_list.size()] = arg_str0(short_desc_c, long_desc_c, NULL, full_desc_c) ; //create and save option-pointer
	type_list[type_list.size()] = ARGTYPE_STRING ; // save type
}

/**
 * Adds a string option to the optionlist
 * @param arg pointer to a arg_int structure (see ArgTable2 documentation)
 */
void ArgumentParser::addStringOption(arg_str* arg)
{
	arg_list[arg_list.size()] = arg ; // just save the option
	type_list[type_list.size()] = ARGTYPE_STRING ; // save type
}

/**
 * Returns a string option for the optionlist
 * @param short_desc Short name for the option (e.g. "v" for "-v" as argument)
 * @param long_desc Long name for the integer (e.g. "version" for "--version" as argument)
 * @param full_desc Description for the parameter, printed in the help message
 * @return the pointer to the arg_int struct (see Argtable2 documentation)
 */
arg_str* ArgumentParser::createStringOption(const std::string&  short_desc, const std::string&  long_desc, const std::string&  full_desc)
{
	char* short_desc_c = copystr(short_desc);
	char* long_desc_c = copystr(long_desc);
	char* full_desc_c = copystr(full_desc);
	c_buffers.push_back(short_desc_c);
	c_buffers.push_back(long_desc_c);
	c_buffers.push_back(full_desc_c);
	
	return arg_str0(short_desc_c, long_desc_c, NULL, full_desc_c) ; // create option with library funcion and return pointer
}

/**
 * The value of an integer option 
 * @param long_desc LONG description of the argument
 * @return the value of a string option, or "" if an error occured
 */
std::string ArgumentParser::getStringValue(const std::string&  long_desc)
{
	for (int i = 0; i < arg_list.size(); i++)
	{
		if (strcmp(((struct arg_int*)arg_list.at(i))->hdr.longopts, long_desc.c_str()) == 0)
		{
			if (type_list.at(i) != ARGTYPE_STRING)
				return "";
			return ((struct arg_str*)arg_list.at(i))->sval[0] ;
		}
	}
	return "";
}

/**
 * Adds a string option to the optionlist
 * @param intopt integer option to add
 */
ArgumentParser& ArgumentParser::operator<<(arg_str* intopt)
{
	arg_list[arg_list.size()] = intopt ; // Save integer-pointer
	type_list[type_list.size()] = ARGTYPE_STRING ; //save type 
	return *this ;
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
	void** argtable = new void*[arg_list.size()] ;// initialize array
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
	delete [] argtable;
	return ret ;
}

/**
 * Checks whether a flag is set or not. 
 * @param long_desc LONG description of the argument
 * @return true if the flag is set, false if not or if it does not exist
 */
bool ArgumentParser::isFlagSet(const std::string&  long_desc)
{
	for (int i = 0; i < type_list.size(); i++) // Look through typelist until ...
	{
		if (type_list.at(i) == ARGTYPE_FLAG) // ... you find a flag and ...
		{
			if(strncmp(((struct arg_lit*)arg_list.at(i))->hdr.longopts, long_desc.c_str(),25) == 0) // .. check if it is the desired one and ...
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
	fprintf (f,"Usage: %s", prog_name.c_str()) ; // print program name
	arg_print_syntax(f,argtable,"\n"); // why reinvent the wheel?
	arg_print_glossary(f,argtable,"  %-25s %s\n"); // dito
}

/**
 * Generates error message out of last error (if occured) and prints it
 * @param f File pointer to print msg to (stderr by default) 
 */
void ArgumentParser::lastError(FILE* f)
{
	arg_print_errors(f, getEnd(), prog_name.c_str()) ; // get Argtable and print it with library function
}

struct arg_end* ArgumentParser::getEnd()
{
	if (type_list[type_list.size()-1] == ARGTYPE_END) // check if there is an end just for security reasons
		return (struct arg_end*)arg_list[arg_list.size()-1] ;
}
