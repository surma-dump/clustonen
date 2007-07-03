#ifndef FOOCLIENTSOCKETFOO
#define FOOCLIENTSOCKETFOO

#include "Socket.h"

class ClientSocket : public Socket
{
public:
	ClientSocket(std::string host, int port) ; // Constructor
	virtual ~ClientSocket() ; // Destructor
		
protected:
	void connect(std::string host, int port) ; 

private:
} ;

#endif 
