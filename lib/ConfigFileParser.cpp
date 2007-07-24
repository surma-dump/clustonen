/**
 * Copyright (C) 2007  Andi Drebes <hackbert@drebesium.org>
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

#include "ConfigFileParser.h"
#include "strhelper.h"
#include <fstream>

/**
 * Constructor. Automatically parses the file specified
 * @param filename The file to be parsed
 */
ConfigFileParser::ConfigFileParser(const std::string& filename)
	: filename(filename)
{
	parse();
}

/**
 * Parses a file
 * @param filename The file to be parsed
 */
void ConfigFileParser::parse()
{
	std::fstream fp(filename.c_str(), std::ios::in);

	if(!fp.good())
		throw ConfigFileParserException("Could not open file \""+filename+"\"");
	
	std::string line;
	while(!fp.eof())
	{
		getline(fp, line);
		
		//delete comments
		int pos = line.find_first_of("#");
		if(pos != std::string::npos)
			line.erase(pos);
		
		//delete leading and trailing whitespace
		trim(line);

		if(line == "")
			continue;
		
		std::string lhs = line.substr(0, line.find_first_of(" \t"));
		std::string rhs = line.substr(line.find_first_of(" \t"));
		trim(lhs);
		trim(rhs);

		values.insert(std::make_pair(lhs, rhs));
	}

	fp.close();
}

/**
 * Returns a key's value
 * @param key the key
 */
std::string ConfigFileParser::getValue(const std::string& key)
{
	std::map<std::string,std::string>::iterator iter = values.find(key);
	if(iter != values.end())
		return iter->second;
	
	return "";
}

/**
 * Returns the number of values read from the file
 */
unsigned int ConfigFileParser::getNumValues()
{
	return values.size();
}

/**
 * Returns a map with all the values from the config file
 */
const std::map<std::string,std::string>& ConfigFileParser::getValues()
{
	return values;
}

ConfigFileParserException::ConfigFileParserException(const std::string& msg)
	: Exception(msg)
{
}
