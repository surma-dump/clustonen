#ifndef FOOSERVERSOCKETFOO
#define FOOSERVERSOCKETFOO

#include "Socket.h"

class ServerSocket : public Socket
{
public:
	ServerSocket(int port) ; // Constructor
	virtual ~ServerSocket() ; // Destructor
		
	void waitForConnection() ; // accept incoming connections

protected:
	void bind(int port) ; // bind socket to port
	void listen() ; // listen for connections

private:
} ;

#endif 
