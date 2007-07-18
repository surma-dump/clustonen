#include "MessageManager.h"

/**
 * Standard constructor
 */
MessageManager::MessageManager()
{
}

/**
 * Destructor
 */
MessageManager::~MessageManager()
{
}

/**
 * Pushes a new message into the message quere
 * @param msg New message to queue
 */
void MessageManager::queueMessage (ClustonenMessage* msg)
{
	messages.push(msg) ;
}

/**
 * Distributes the next message in line to all hooked modules.
 */
void MessageManager::distributeNext()
{
	if (messages.size() > 0)
	{
		ClustonenMessage* msg = messages.front() ;
		messages.pop() ;
		std::list<ClustonenModule*> modules = modulelist[msg->getName()] ;
		for (std::list<ClustonenModule*>::iterator module = modules.begin(); module != modules.end(); module++)
			(*module)->processMessage(msg) ;
	}
}
