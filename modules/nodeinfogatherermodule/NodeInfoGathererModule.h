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

#ifndef FOONODEINFOGATHERERMODULEFOO
#define FOONODEINFOGATHERERMODULEFOO

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "ClustonenModule.h"
#include "ClustonenMessage.h"

/**
 * Module for gathering information about a node
 */
class NodeInfoGathererModule : ClustonenModule
{
public:
	NodeInfoGathererModule() ; // Constructor
	virtual ~NodeInfoGathererModule() ; // Destructor
		
	std::string getName() ; // returns plugin's name

	int processMessage(ClustonenMessage* msg); // Called when a appropiate message hits chain

	std::string getHostname() const;
	int getNumInterfaces() const;
	//std::string getInterface(int num);
	std::string getRunningKernel() const;
	//std::string getRamStatus();
	//std::string getProcesslist();
protected:	
private:
} ;

#endif
