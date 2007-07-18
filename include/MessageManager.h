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
