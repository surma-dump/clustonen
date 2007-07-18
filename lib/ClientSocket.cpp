#include "ClientSocket.h"

/**
 * Creates a socket and connects it to a host
 * @param host Ip of the host to connect to
 * @param port Port on which to connect
 */
ClientSocket::ClientSocket(std::string host, int port) : Socket()
{
	connect(host, port) ; // connect to host
}

/**
 * Standard destructor
 */
ClientSocket::~ClientSocket()
{
	close() ; // shut everything down
}

/**
 * Connect socket to a host
 * @param host IP of the host to connect to as a string
 * @param port Port to use for the connection
 */

void ClientSocket::connect(std::string host, int port)
{
	memset(&opponentsocket, 0, sizeof (opponenthandle)) ; // Zero out struct
	opponentsocket.sin_family = AF_INET ; // TCP/IP-Socket
	opponentsocket.sin_addr.s_addr = inet_addr(host.c_str()) ; // Connecto to where?
	opponentsocket.sin_port = htons(port) ; // On which port?
	
	opponenthandle = ::connect (sockethandle, (struct sockaddr*)&opponentsocket, sizeof (opponentsocket)) ; // actually connect
	if (opponenthandle < 0) // and if it failed...
		throw Exception ("Could not connect to host. \n") ; // throw exception
	connected = true ;
	transmissionhandle = sockethandle ;
}
