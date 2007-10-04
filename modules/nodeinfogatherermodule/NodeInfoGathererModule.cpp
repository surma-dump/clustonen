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

#include "NodeInfoGathererModule.h"

/**
 * Standard Constructor
 */
NodeInfoGathererModule::NodeInfoGathererModule()
{
}

/**
 * Destructor
 */
NodeInfoGathererModule::~NodeInfoGathererModule()
{
}

std::string NodeInfoGathererModule::getName()
{
	return "NodeInfoGathererModule" ;
}

int NodeInfoGathererModule::processMessage (ClustonenMessage* msg)
{
	// There are only certain values required
	if (msg->getNumFields() > 0)
	{
	}
	else // everything is wanted
	{
		
	}
	return CHAIN_PROCEED ;
}
