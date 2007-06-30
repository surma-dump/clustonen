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
		const char*		read() ; // read incoming message

	protected:
		void			bind(int port) ; // bind socket to port
		void			listen() ; // listen for connections

	private:
		int			sockethandle ; 
		int			opponenthandle;
		char			msg[MAXLEN + 1] ;
		struct sockaddr_in 	srv ;
} ;

#endif 
