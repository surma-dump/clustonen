#include "ServerSocket.h"

/**
 * Creates a socket and binds it to a port
 * @param port Port to bind to
 */
ServerSocket::ServerSocket(int port) : Socket()
{
	bind(port) ; // Bind it to a port
	listen() ; // and make it listen to it
}

/**
 * Standard destructor
 */
ServerSocket::~ServerSocket()
{
	close() ; // shut everything down
}

/**
 * Binds the socket to a port
 * @param port Port to bind to
 */
void ServerSocket::bind(int port)
{
	memset (&serversocket, 0, sizeof(serversocket)) ; // zero out the struct
	serversocket.sin_family = AF_INET; // set TCP,...
	serversocket.sin_addr.s_addr = INADDR_ANY ; // No special interface (yet)
	serversocket.sin_port = htons(port) ; // port
	
	if (::bind(sockethandle, (struct sockaddr *)&serversocket, sizeof (struct sockaddr)) != 0) // Try to bind the socket to the port
		throw  Exception ("ClustonenLib: Could not bind to Socket. \n") ; // and throw an exception if it failed
}

/**
 * Sets the socket to listening mode
 * @param pendings Allow this number of pending connections 
 */
void ServerSocket::listen()
{
	if (::listen(sockethandle, 1) != 0) // set it to listen
		throw  Exception ("ClustonenLib: Could not switch to listening mode. \n") ; // and throw an exception if it failed
}

/**
 * Waits for an connection request and accepts it
 */
void ServerSocket::waitForConnection()
{
	socklen_t socksize = sizeof(struct sockaddr_in) ; 
	opponenthandle = ::accept(sockethandle, (struct sockaddr *) &opponentsocket, &socksize) ; // just wait and save sockethandle of the incoming connection
	if (opponenthandle < 0)
		throw Exception ("Could not accept connection. \n") ;
	connected = true;
	transmissionhandle = opponenthandle ;
}



