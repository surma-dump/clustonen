#ifndef FOOSOCKETFOO
#define FOOSOCKETFOO

#include <arpa/inet.h>
#include <string>
//#include <netdb.h>
//#include <netinet/in.h>
#include "Exception.h"
#include "errno.h"

#define MAXLEN 256

class ServerSocket
{
	public:
					ServerSocket(int port) ; // Constructor
					~ServerSocket() ; // Destructor
		
		void			waitForConnection() ; // accept incoming connections
		void			close(); // close socket
		void			disconnect() ; // disconnects from opponent

		void			write(const char* msg, int len) ; // write message to connected host
		int			read() ; // read incoming message

		const char*		getMessage() ; // returns saved message
		bool			isConnected() ; 
		std::string		getOpponent() ; // IP of the opponent
		int			getPort() ;

	protected:
		void			bind(int port) ; // bind socket to port
		void			listen() ; // listen for connections

	private:
		int			sockethandle ; 
		int			opponenthandle;
		struct sockaddr_in 	serversocket ;
		struct sockaddr_in 	opponentsocket;
		char			msg[MAXLEN + 1] ;
} ;

#endif 
