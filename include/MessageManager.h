/**
 * Copyright (C) 2007  Alexander Surma <crock@drebesium.org>
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

#ifndef FOOMESSAGEMANAGERFOO
#define FOOMESSAGEMANAGERFOO

#include <string>
#include <map> 
#include <list>
#include <queue>
#include "ClustonenModule.h"
#include "ClustonenMessage.h"
#include "ClustonenMutex.h"

/**
 * Manager for processing Messages
 */
class MessageManager
{
public:
	MessageManager () ;
	virtual	~MessageManager() ; 

	// Queues a message
	void queueMessage (ClustonenMessage* msg) ;

	// Distributes next message in line to hooked modules
	void distributeNext() ;

	void addModuleHook(const std::string& msgName, ClustonenModule* module);
	void removeModuleHook(const std::string& msgName, ClustonenModule* module);
	void removeModuleHook(ClustonenModule* module);
	
protected:
private:
	// Message type string as key, results in a list of modules processing this event.
	std::map<std::string, std::list<ClustonenModule*> > modulelist ; 
	std::queue<ClustonenMessage*> messages ;
	ClustonenMutex* modulelist_mutex;
	ClustonenMutex* queue_mutex;
} ;

#endif
