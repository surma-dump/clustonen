#ifndef FOOSOCKETFOO
#define FOOSOCKETFOO

#include <arpa/inet.h>
#include <string>
//#include <netdb.h>
//#include <netinet/in.h>
#include "Exception.h"
#include "errno.h"

#define MAXLEN 255

class Socket
{
public:
	Socket() ; // Constructor
	virtual ~Socket() ; // Destructor
		
	void disconnect() ; // disconnects from opponent
	void close(); // close socket

	void write(const char* msg, int len) ; // write message to connected host
	int read() ; // read incoming message

	const char* getMessage() ; // returns saved message
	bool isConnected() ; 
	std::string getOpponent() ; // IP of the opponent
	int getPort() ;

protected:
	int sockethandle ; 
	int opponenthandle;
	int transmissionhandle ;
	struct sockaddr_in serversocket ;
	struct sockaddr_in opponentsocket;
	bool connected ;
	char msg[MAXLEN + 1] ;

private:
} ;

#endif 
