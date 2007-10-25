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

#ifndef TESTMODULE_H
#define TESTMODULE_H

#include "ClustonenModule.h"
#include "ClustonenMessage.h"

/**
 * Just a silly test module
 */
class TestModule : ClustonenModule
{
public:
  TestModule(PluginEnvironment *pe, bool server_mode) ;
	virtual ~TestModule() ;
	
	// returns plugin's name
	std::string getName() ;

	// Called when a appropiate message hits chain
	int processMessage(ClustonenMessage* msg);

protected:
	//client or server mode. true = servermode
	bool server_mode;
} ;

#endif //TESTMODULE_H
