
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
#include "MessageManager.h"
#include "strhelper.h"
#include "Server.h"

/**
 * Standard Constructor
 */
NodeInfoGathererModule::NodeInfoGathererModule(PluginEnvironment *pe)
	: ClustonenModule(pe)
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
	ret.setName("NodeInfo");
	// If this is not a request for information, what is it doing here anyways?!
	if (msg->getName() != "NodeInfoRequest") 
		return -1;
	
	//Walk through every field in the Message
	for (int i = 0; i < msg->getNumFields(); i++)
	{ 
		// We just suppose there only "Attribute<x>" formatted fields
		// and don't bother to look at the rest. 

		std::string attr = msg->getField("Attribute"+i);
		// Check what is requested and give it to 'em if possible
		if (attr == "Hostname") 
			ret.addField("Hostname", getHostname()) ;
		else if (attr == "Kernel")
			ret.addField("Kernel", getRunningKernel());
		else if (attr == "NumInterfaces")
			ret.addField("NumInterfaces", numberToString(getNumInterfaces()));
	}
	pe->getServer()->getMessageManager().sendMessage(&ret);
	// No need to kill the message or obtain it again
	return CHAIN_PROCEED ; 
}

// The stuff below is rather dirty. Please consider it to be temporary

std::string NodeInfoGathererModule::getHostname() const
{
	std::ifstream f;
	f.open("/etc/hostname");
	if(!f)
		return "Could not be determined" ;
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
		return "Could not be determined" ;
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
