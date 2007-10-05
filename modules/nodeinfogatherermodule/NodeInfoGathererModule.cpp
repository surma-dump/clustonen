
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
	ClustonenMessage ret;
	//ret.setName(msg->getOrigin());
	for (int i = 0; i < msg->getNumFields(); i++)
	{
		std::string attr = msg->getField("Attribute"+i);
		if (attr == "Hostname")
			ret.addField("Hostname", getHostname()) ;
		else if (attr == "Kernel")
			ret.addField("Kernel", getRunningKernel());
		else if (attr == "NumInterfaces")
			ret.addField("NumInterfaces", getNumInterfaces);
	}
	//sendMessage(ret);
	return CHAIN_PROCEED ;
}

std::string NodeInfoGathererModule::getHostname() const
{
	std::ifstream f;
	f.open("/etc/hostname");
	if(!f)
		return "Could not be determinded" ;
	std::string p;
	f >> p ;
	f.close() ;
	return p ;
}

std::string NodeInfoGathererModule::getRunningKernel() const
{
	std::ifstream f;
	f.open("/proc/version");
	if(!f)
		return "Could not be determinded" ;
	std::string p,ret;
	while (f >> p) 
	      ret += p + " " ;
	f.close() ;
	return ret ;
}

int NodeInfoGathererModule::getNumInterfaces() const
{
	FILE *f = popen ("cat /proc/net/dev | grep -E \"[a-z0-9+]:\" | wc -l", "r");
	int ret ;
	fscanf (f, "%d", &ret) ;
	return ret ;
}
