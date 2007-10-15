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

#ifndef FOOCLUSTONENMODULEFOO 
#define FOOCLUSTONENMODULEFOO 

#include <cstdio>
#include <cstdlib>
#include "ClustonenMessage.h"

// Forward-Declaration to prevent circular dependencies from screwing everything up
class MessageManager;

/**
 * Abstract class for modules to be loaded by the ModuleManager
 */
class ClustonenModule
{
public:
	ClustonenModule(MessageManager *_mm);
	virtual ~ClustonenModule();

	// TODO Module information methods

	// returns plugin's name
	virtual std::string getName() = 0;

	// TODO Module handling
	// Called when a message the module is hooked for is processed
	virtual int processMessage(ClustonenMessage* msg) = 0;

protected:
	MessageManager *mm ;
} ;

enum {
	CHAIN_STOP = 1,
	CHAIN_PROCEED,
	CHAIN_RESTART
} ;

#endif
