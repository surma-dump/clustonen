#include "Socket.h"

/**
 * Standard constructor, creates a socket
 */
Socket::Socket() 
{
	if ((sockethandle = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		throw new Exception ("Could not initialize Socket") ;
		
}

/**
 * Creates a socket and binds it to a port
 * @param port Port to bind to
 */
Socket::Socket(int port)
{
	Socket();
	bind(port) ;
}

/**
 * Creates a socket from a struckt
 * @param handle handle of a Socket
 * @param data Socketstruckt
 */
Socket::Socket(int handle, struct sockaddr_in data)
{
	sockethandle = handle ;
	srv=data;
}

/**
 * Standard destructor
 */
Socket::~Socket()
{
	close() ;
}

/**
 * Binds the socket to a port
 * @param port Port to bind to
 */
void Socket::bind(int port)
{
	memset (&srv, 0, sizeof(srv)) ;
	srv.sin_family = AF_INET;
	srv.sin_addr.s_addr = INADDR_ANY ;
	srv.sin_port = htons(port) ;
	
	if (::bind(sockethandle, (struct sockaddr *)&srv, sizeof (struct sockaddr)) != 0)
		throw new Exception ("Could not bind to Socket") ;
}

/**
 * Sets the socket to listening mode
 * @param pendings Allow this number of pending connections 
 */
void Socket::listen(int pendings)
{
	if (::listen(sockethandle, pendings) != 0)
		throw new Exception ("Could not switch to listening mode") ;
}

/**
 * Accept incoming connection and return its socket
 * @return Socket incoming connection
 */
Socket Socket::accept()
{
	
	int clienthandle;
	socklen_t socksize = sizeof(struct sockaddr_in) ;
	struct sockaddr_in cl;
	clienthandle = ::accept(sockethandle, (struct sockaddr *) &cl, &socksize) ;
	return Socket(clienthandle, cl) ;	
}

/**
 * Closes the socket and frees everything
 */
void Socket::close()
{
	::close(sockethandle) ;
}

/**
 * Sends a string to the connected host
 * @param msg String to send
 */
void Socket::write(std::string msg)
{
	if (::send(sockethandle,msg.c_str(),msg.length(),0) != 0)
		throw new Exception ("Could not send string") ;
}

/**
 * Receives a string from the connected host
 * @returns the received string
 */
std::string Socket::read()
{
	char msg[MAXLEN + 1] ;
	if (::recv(sockethandle, msg, MAXLEN, 0) < 0)
		throw new Exception ("Could not receive string") ;
	msg[MAXLEN]='\0' ;
	return std::string(msg) ;
}
