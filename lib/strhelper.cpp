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

#include "strhelper.h"
#include <malloc.h>

/**
 * Trims a string (deletes leading and trailing whitespace)
 * @param str the string to be trimmed
 * @param ws the characters to be treated as whitespace
 */
void trim(std::string& str, const std::string& ws)
{	
	str.erase(str.find_last_not_of(ws)+1);
	str.erase(0,str.find_first_not_of(ws));
}

/**
 * Takes a string as an argument and copies it's content to
 * a newly allocated buffer. The buffer will be allocated with
 * the operator new. This function should only be used for compatibility
 * with c libraries. DO NOT OMIT THE RETURN VALUE!
 * @param str The string to be copied
 * @return a newly allocated buffer
 */
char* copystr(const std::string& str)
{
	char* buffer = new char[str.length()];
	strcpy(buffer, str.c_str());
	return buffer;
}
