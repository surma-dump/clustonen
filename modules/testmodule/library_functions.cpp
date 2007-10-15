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

#include "TestModule.h"
#include <iostream>

extern "C" const char* get_identifier()
{
	return "TestModule" ;
}

extern "C" ClustonenModule* get_client_module(MessageManager *_mm)
{
	std::cout << "TestModule: get_client_module() called..." << std::endl;
	return (ClustonenModule*)(new TestModule(_mm, false)) ;
}

extern "C" ClustonenModule* get_server_module(MessageManager *_mm)
{
	std::cout << "TestModule: get_server_module() called..." << std::endl;
	return (ClustonenModule*)(new TestModule(_mm, true)) ;
}