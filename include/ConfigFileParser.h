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

#ifndef CONFIGFILEPARSER_H
#define CONFIGFILEPARSER_H

#include "Exception.h"

#include <string>
#include <map>

class ConfigFileParser {
	public:
		ConfigFileParser(const std::string& filename);

		void parse();
		std::string getValue(const std::string& key);
		unsigned int getNumValues();
		const std::map<std::string,std::string>& getValues();

	protected:
		std::string filename;
		std::map<std::string, std::string> values;
};

class ConfigFileParserException : public Exception
{
	public:
		ConfigFileParserException(const std::string& msg);
};

#endif //CONFIGFILEPARSER_H
