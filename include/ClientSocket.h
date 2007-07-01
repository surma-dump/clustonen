#ifndef FOOCLIENTSOCKETFOO
#define FOOCLIENTSOCKETFOO

#include <Arpa/inet.H>
#include <string>
//#include <netdb.h>
//#include <netinet/in.h>
#include "Exception.h"
#include "errno.h"

#define MAXLEN 256

class ClientSocket
{
	public:
					ClientSocket(std::string host, int port) ; // Constructor
					~ClientSocket() ; // Destructor
		
		void			close(); // close socket

		void			write(const char* msg, int len) ; // write message to connected host
		int			read() ; // read incoming message

		const char*		getMessage() ; // returns saved message
		bool			isConnected() ; 
		std::string		getOpponent() ; // IP of the opponent
		int			getPort() ;

	protected:
		void /*!!!*/ connect(std::string host, int port) ; 

	private:
		int			sockethandle ; 
		int			opponenthandle;
		struct sockaddr_in 	clientsocket ;
		struct sockaddr_in 	opponentsocket;
		char			msg[MAXLEN + 1] ;
} ;

#endif 
