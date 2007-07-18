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

#ifndef FOOTESTMODULEFOO 
#define FOOTESTMODULEFOO 

#define AUTHOR "Alexander \"crock\" Surma <crock@drebesium.org>"

#include <cstdio>
#include <cstdlib>
#include "ClustonenModule.h"
#include "ClustonenEvent.h"


/**
 * Module for testing
 */
class TestModule : ClustonenModule
{
public:
	TestModule() ; // Constructor
	virtual ~TestModule() ; // Destructor
		
	const char* getName(); // returns plugin's name
	int getHookPosition(); // returns the desired hook to chain the module to

	int processEvent(ClustonenEvent& event); // Called when a appropitate event hits chain
protected:
private:
} ;

#endif
