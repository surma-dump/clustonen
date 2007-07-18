#ifndef FOOSOCKETQUEUEFOO
#define FOOSOCKETQUEUEFOO

#define AUTHOR "Alexander \"crock\" Surma <crock@drebesium.org>"

#include <cstdio> 
#include <cstdlib> 
#include <queue>

/**
 * Opens a socket, accepts connection and puts client into a queue (hence the inheritance), while a new socket has already been opened.
 */
class SocketQueue
{
public:
	SocketQueue(int port) ; // Constructor
	virtual	~SocketQueue() ; // Destructor
protected:
private:
//std::queue connection_queue ;
} ;


#endif
