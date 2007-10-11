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

#include <iostream>
#include <cstdlib>
#include "ClustonenModule.h"
#include "ClustonenMessage.h"
#include "ModuleManager.h"

typedef ClustonenModule* (*get_module_func)(void) ; // will return an instance of the module
typedef const char* (*get_identifier_func)(void) ; // will return an unique identifer

int main()
{
	ModuleManager mm ;
	ClustonenModule *cm ;
	std::string s = mm.loadModule("../../modules/nodeinfogatherermodule/libclustonen_nodeinfogatherermodule.so");
	std::cout << s << std::endl ;
	cm = mm.getModule(s, MODULE_SIDE_CLIENT);
	std::cout << cm->getName() << std::endl;
}
