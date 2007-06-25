#ifndef FOOSOCKETFOO
#define FOOSOCKETFOO

#include <arpa/inet.h>
#include <string>
//#include <netdb.h>
//#include <netinet/in.h>
#include "Exception.h"

#define MAXLEN 256

class Socket
{
	public:
					Socket() ;// Constructor
					Socket(int port) ; // s.a. including bind-call
					Socket(int handle, struct sockaddr_in data) ;
					~Socket() ; // Destructor
		
		void			bind(int port) ; // bind socket to port
		void			listen(int pendings = 1) ; // listen for connections
		Socket			accept() ; // accept incoming connections
		void			connect(std::string ip, int port) ; // connect socket to host
		void			close(); // close socket

		void			write(std::string msg) ; // write message to connected host
		std::string		read() ; // read incoming message

	private:
		int			sockethandle ; 
		struct sockaddr_in 	srv ;
} ;

#endif 
