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

#include <ConfigParser.h>
#include <fstream>

ConfigParserException::ConfigParserException(const std::string& msg)
	: Exception(msg)
{
}

/**
 * Standard constructor
 * @param filename The file to be parsed
 */
ConfigParser::ConfigParser(const std::string& filename)
{
	this->filename = filename;
}

/**
 * Parses the configuration file
 */
void ConfigParser::parse()
{
	std::ifstream fp(filename.c_str());
	
	///FIXME: line length is limited to 1024 characters
	char buffer[1024];
	
	if(!fp)
		throw ConfigParserException("Could not open file " + filename);
	
	//Main loop: let's read the file's lines
	while(fp.getline(buffer, sizeof(buffer)))
	{
		std::string line = buffer;
		line.substr(0, line.find('#'));
	}
}

/**
 * Returns a key's value as a string
 * @param key the key whose value should be returned
 * @return the key's value
 */
std::string ConfigParser::getStringValue(const std::string& key)
{
}

/**
 * Returns a key's value as an integer
 * @param key the key whose value should be returned
 * @return the key's value
 */
int ConfigParser::getIntValue(const std::string& key)
{
}

/**
 * Returns a key's value as a bool
 * @param key the key whose value should be returned
 * @return the key's value
 */
bool ConfigParser::getBoolValue(const std::string& key)
{
}
