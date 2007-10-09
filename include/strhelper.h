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

#ifndef STRHELPER_H
#define STRHELPER_H

#include <string>
#include <vector>

void trim(std::string& str, const std::string& ws = "\t ");
char* copystr(const std::string& str);
void replacestr(const std::string& needle, const std::string& replacement, std::string& haystack);
std::string numberToString(double num);

#endif //STRHELPER_H
