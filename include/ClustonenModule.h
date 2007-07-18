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

#define AUTHOR "Alexander \"crock\" Surma <crock@drebesium.org>"

#include <cstdio>
#include <cstdlib>
#include "ClustonenMessage.h"


/**
 * Abstract class to interact with modules (provided by the module itself)
 */
class ClustonenModule
{
public:
	ClustonenModule() ; // Constructor
	virtual ~ClustonenModule() ; // Destructor
		
	//TODO Module information methods
	virtual const char* getName() = 0; // returns plugin's name

	// TODO Module handling
	virtual int processMessage(ClustonenMessage* msg) = 0; // Called when a message is processed, the module is hooked for
protected:
private:
} ;

#endif
