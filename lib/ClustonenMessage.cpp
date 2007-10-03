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

#include "ClustonenMessage.h"
#include "strhelper.h"

#include <iostream>  // dito

/**
 * Standardconstructor
 */
ClustonenMessage::ClustonenMessage()
{
}

/**
 * Constructor with initialization
 * @param name Identifier of the message
 * @param data Data of the message (see class definition)
 */
ClustonenMessage::ClustonenMessage(const std::string& _name, const std::string& _data)
{
	name = _name ;
	parse (_data) ;
}

/**
 * Constructor for a message. Works as the reversion of toString()
 * @param pack String created by toString()
 */
ClustonenMessage::ClustonenMessage(const std::string& pack)
{
	int len ;
	char *buf ;
	char _name[MAXFIELDNAME] ;
	regex_t regex ; // Compiled RegEx
	regmatch_t matches[2] ; // Buffer for matches. 1 for the expression and 3 subexpressions
	buf = (char *) malloc (pack.length() * sizeof(char)) ;
	memcpy (buf, pack.c_str(), pack.length()) ;

	if (regcomp (&regex, "\\s*([-_a-zA-Z0-9]+)\\s*|", REG_EXTENDED) != 0) // compile regex and chech if it succeeded
		throw Exception ("Could not parse data, error while compiling regular expression. \n") ; // if not, throw an exception
	if(regexec (&regex, buf, 2, matches, 0) != 0) // If there's no name-definition, the message is invalid
		throw Exception ("Message has no name") ;

	memset (_name, 0, MAXFIELDNAME) ; // Fill with zero, so we don't have to set it manually afterwards
	memcpy (_name, &buf[matches[1].rm_so], matches[1].rm_eo - matches[1].rm_so) ; // copy <length of match> chars from <beginning of match> to name
	name = _name ; // Save isolated name
	regfree(&regex) ; 
	len = strlen (buf) ; // save old length of buffer
	memcpy (&buf[matches[0].rm_so], &buf[matches[0].rm_eo+1], pack.length() - matches[0].rm_eo) ; // goto beginning of match, and move the everything from the end of the match to there (the match itself is overwritten).
	buf[matches[0].rm_so + (len - matches[0].rm_eo)] = '\0' ; // terminate at the new end
	parse (buf) ; // and let the rest be done by parse()
}

/**
 * Destructor
 */
ClustonenMessage::~ClustonenMessage()
{
}

/**
 * Get name of message
 * @return Name of the message as a string
 */
std::string ClustonenMessage::getName() const
{
	return name ;
}

/**
 * Get value of a data filed
 * @param field  Name of the field
 * @return Value of the field with the name defined above
 */
std::string ClustonenMessage::getField(const std::string& field) const
{
	std::map<std::string,std::string>::const_iterator it = data.find(field);
	
	if(it != data.end())
		return it->second;
	
	return "";
}

void ClustonenMessage::unescapeData(std::string& _data)
{
	replacestr("\\'", "'", _data);
}

/**
 * Formats the saved data as a string
 * @return data as a string
 */
std::string ClustonenMessage::getData() const
{
	std::string ret = "" ;
	for (std::map<std::string, std::string>::const_iterator dataseg=data.begin(); dataseg != data.end(); dataseg++) // Run through every data segment
		ret += dataseg->first+"='"+dataseg->second+"';" ; // and append it formatted to the string
	return ret ;
}

/**
 * Sets the name of the message
 * @param _name New name of the message
 */
void ClustonenMessage::setName(const std::string& _name)
{
	name = _name ;
}

/**
 * Deletes all previously saved data and parses the given string for new data
 * @param _data New data as a string
 */
void ClustonenMessage::setData (const std::string& _data)
{
	parse (_data) ;
}

/**
 * Parses a string for data and adds the result to the previously save data. Already existing keys will be overwritten.
 * @param _data Additional data as a string
 */
void ClustonenMessage::addData (const std::string& _data)
{
	parse(getData() + _data) ; // Get old data and append new one
}

/**
* Adds a single field with value to the data
 * @param field Name of the field to add
 * @param value Value to assign to the field
 */
void ClustonenMessage::addField(const std::string& field, const std::string& value)
{
	data[field] = value ;
}

/**
 * Deletes a field from the saved data
 * @param field Name of the field to delete
 */
void ClustonenMessage::delField(const std::string& field)
{
	data.erase(field) ;
}

/**
 * Converts the message to a string usable by the 3rd constructor
 * @return string representing the message
 */
std::string ClustonenMessage::toString() const
{
	return name+"|"+getData() ;
}

/**
 * Parses the given string and fills it into the data map
 * @param _data string to parse
 */
void ClustonenMessage::parse(const std::string& _data)
{
	int len ;
	char *buf ;
	char field[MAXFIELDNAME], value[MAXFIELDVALUE] ;
	regex_t regex ; // Compilated RegEx
	regmatch_t matches[4] ; // Buffer for matches. 1 for the expression and 3 subexpressions

	buf = (char *) malloc (_data.length() * sizeof(char)) ;
	memcpy (buf, _data.c_str(), _data.length()) ;

	if (regcomp (&regex, "\\s*([-_a-zA-Z0-9]+)\\s*=\\s*'(([^\\']|\\\\.)+)'\\s*;", REG_EXTENDED) != 0) // compile regex and chech if it succeeded
		throw Exception ("Could not parse data, error while compiling regular expression. \n") ; // if not, throw an exception
	while (regexec (&regex, buf, 4, matches, 0) == 0) // As long as there are matches, fill them into the matches-struct-array...
	{
		memset (field, 0, MAXFIELDNAME) ; // Fill with zero, so we don't have to set it manually afterwards
		memset (value, 0, MAXFIELDVALUE) ; // -- " --
		memcpy (field, &buf[matches[1].rm_so], matches[1].rm_eo - matches[1].rm_so) ; // copy <length of match> chars from <beginning of match> to field
		memcpy (value, &buf[matches[2].rm_so], matches[2].rm_eo - matches[2].rm_so) ; // -- " -- to value
		data[field] = std::string(value) ; // Add the field and the value to the map
		unescapeData(data[field]);
		len = strlen(buf) ; // save old length of buffer
		memcpy (&buf[matches[0].rm_so], &buf[matches[0].rm_eo], strlen(buf) - matches[0].rm_eo) ; // goto beginning of match, and move the everything from the end of the match to there (the match itself is overwritten). 
		buf[matches[0].rm_so + (len - matches[0].rm_eo)] = '\0' ; // terminate at the new end
	}
	regfree(&regex) ;
}
