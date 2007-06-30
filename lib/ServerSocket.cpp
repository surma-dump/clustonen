#include "ServerSocket.h"

/**
 * Creates a socket and binds it to a port
 * @param port Port to bind to
 */
ServerSocket::ServerSocket(int port)
{
	sockethandle = socket(AF_INET, SOCK_STREAM, 0) ; // Create socket
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
}

/**
 * Closes the connection, if present, and destroys socket
 */
void ServerSocket::close()
{
	disconnect() ; // close opponent's socket
	::close(sockethandle) ; // and after that yourself
}

/**
 * Closes the connection to opponent, if connected
 */
void ServerSocket::disconnect()
{
	if (opponenthandle != -1) // if there's an actual connection
		::close(opponenthandle) ; // close it
	opponenthandle = -1 ; 
}

/**
 * Sends a bytesequence to the connected host
 * @param msg bytesequence to send
 */
void ServerSocket::write(const char* msg, int len)
{
	if (::send(opponenthandle,msg,len,0) < 0) // Write sequence to socket
		throw  Exception ("ClustonenLib: Could not send string. \n") ; // and throw exception if it failed
}

/**
 * Receives a string from the connected host
 * @returns Number of bytes received 
 */
int ServerSocket::read()
{
	memset(msg, 0, MAXLEN+1); // Zero out buffer
	int num = ::recv(opponenthandle, msg, MAXLEN, MSG_WAITALL) ; // Receive sequence and save length
	if (num < 0) // if it failed, num will be -1
		throw Exception ("ClustonenLib: Could not receive byte sequence. \n") ;  // and therefore an exception will be thrown
	return num ;
}

/**
 * Returns the char array conatining sequence received in previous transmissions
 * @returns previous transmissions
 */
const char* ServerSocket::getMessage()
{
	return msg ;
}

/**
 * checks whether this socket is part of a connection
 * @returns true if it is, false otherwise
 */
bool ServerSocket::isConnected()
{
	return opponenthandle != -1 ; // Opponenhandle is -1 if no connection is present
}

/**
 * Gives IP of connected opponent
 * @returns IP of connected opponent, NULL if none
 */
std::string ServerSocket::getOpponent()
{
	if (opponenthandle == -1)
		return NULL ;
	return inet_ntoa(opponentsocket.sin_addr) ;
}
