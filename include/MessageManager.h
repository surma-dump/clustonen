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

#ifndef FOOMESSAGEMANAGERFOO
#define FOOMESSAGEMANAGERFOO

#define AUTHOR "Alexander \"crock\" Surma <crock@drebesium.org>"

#include <cstdio> 
#include <cstdlib> 
#include <string>
#include <map> 
#include <list>
#include <queue>
#include "ClustonenModule.h"
#include "ClustonenMessage.h"
/**
 * Manager for processing Messages
 */
class MessageManager
{
public:
	MessageManager () ; // Constructor
	virtual	~MessageManager() ; // Destructor
	void queueMessage (ClustonenMessage* msg) ; // Queues a message
	void distributeNext() ; // Distributes next message in line to hooked modules
protected:
private:
	std::map<std::string, std::list<ClustonenModule*> > modulelist ; // Message type string as key, results in a list of modules processing this event.
	std::queue<ClustonenMessage*> messages ;
} ;


#endif