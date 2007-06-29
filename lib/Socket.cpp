#include "Socket.h"

/**
 * Standard constructor, creates a socket
 */
Socket::Socket() 
{
	if ((sockethandle = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		throw  Exception ("Could not initialize Socket") ;
		
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
		throw  Exception ("Could not bind to Socket") ;
}

/**
 * Sets the socket to listening mode
 * @param pendings Allow this number of pending connections 
 */
void Socket::listen(int pendings)
{
	if (::listen(sockethandle, pendings) != 0)
		throw  Exception ("Could not switch to listening mode") ;
}

/**
 * Accept incoming connection and return its socket
 * @return Socket incoming connection
 */
void Socket::accept()
{
	socklen_t socksize = sizeof(struct sockaddr_in) ;
	struct sockaddr_in cl;
	opponenthandle = ::accept(sockethandle, (struct sockaddr *) &cl, &socksize) ;
}

/**
 * Connects the socket to a host
 * @param ip Ip as a string
 * @param port Port to connect to
 */
void Socket::connect(const std::string& ip, int port)
{
	struct sockaddr_in dst;
	memset (&dst, 0, sizeof (dst)) ;
	dst.sin_family = AF_INET ;
	dst.sin_addr.s_addr = inet_addr(ip.c_str()) ;
	dst.sin_port = htons (port) ;
	if (::connect(sockethandle, (struct sockaddr *)&dst, sizeof (struct sockaddr)) != 0)
		throw  Exception ("Could not connect to host") ;
}

/**
 * Closes the socket and frees everything
 */
void Socket::close()
{
	::close(opponenthandle) ;
	::close(sockethandle) ;
}

/**
 * Sends a string to the connected host
 * @param msg String to send
 */
void Socket::write(const std::string& msg)
{
	if (::send(opponenthandle,msg.c_str(),msg.length(),0) != 0)
		throw  Exception ("Could not send string") ;
}

/**
 * Receives a string from the connected host
 * @returns the received string
 */
std::string Socket::read()
{
	char msg[MAXLEN + 1] ;
	memset(msg, 65, MAXLEN+1);
	std::string s = "" ;
	switch(::recv(sockethandle, msg, MAXLEN, 0))
	{
		case -EBADF: s = "EBADF" ; break;
		case -ECONNREFUSED: s = "CONNREF"; break;
		case -ENOTCONN: s = "NOTCON"; break ;
		case -ENOTSOCK: s = "NOSOCK"; break ;
		case -EAGAIN: s = "TIMEOUT"; break ;
		case -EINTR: s = "INTER" ; break ;
		case -EINVAL: s = "INVALID"; break ;
		case -ENOMEM: s = "NOMEM"; break ;
		default: s = "HUH?!"; break ;
	}
	printf ("error: %s", s.c_str()) ;
		//throw  Exception ("Could not receive string") ;
	msg[MAXLEN]='\0' ;
	return std::string(msg) ;
}
