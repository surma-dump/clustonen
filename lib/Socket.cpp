#include "Socket.h"

/**
 * Creates a socket
 */
Socket::Socket()
{
	sockethandle = socket(AF_INET, SOCK_STREAM, 0) ; // Create socket in store its handle
	memset (msg, 0, MAXLEN) ;
	connected = false ;
	transmissionhandle = -1 ;
}

/**
 * Standard destructor
 */
Socket::~Socket()
{
	close() ;
}

/**
 * Closes the connection to opponent, if connected
 */
void Socket::disconnect()
{
	if (isConnected()) // if there's an actual connection
		::close(opponenthandle) ; // close it
	connected = false ;
}

/**
 * Closes the connection, if present, and destroys socket
 */
void Socket::close()
{
	disconnect() ; // close opponent's socket
	::close(sockethandle) ; // and after that yourself
	connected = false ;
	transmissionhandle = -1 ;
}

/**
 * Sends a bytesequence to the connected host
 * @param msg bytesequence to send
 */
void Socket::write(const char* msg, int len)
{
	if (::send(transmissionhandle,msg,len,0) < 0) // Write sequence to socket
		throw  Exception ("ClustonenLib: Could not send string. \n") ; // and throw exception if it failed
}

/**
 * Receives a string from the connected host
 * @returns Number of bytes received 
 */
int Socket::read()
{
	memset(msg, 0, MAXLEN+1); // Zero out buffer
	int num = ::recv(transmissionhandle, msg, MAXLEN, 0) ; // Receive sequence and save length
	if (num < 0) // if it failed, num will be -1
		throw Exception ("ClustonenLib: Could not receive byte sequence. \n") ;  // and therefore an exception will be thrown
	return num ;
}

/**
 * Returns the char array conatining sequence received in previous transmissions
 * @returns previous transmissions
 */
const char* Socket::getMessage()
{
	return msg ;
}

/**
 * checks whether this socket is part of a connection
 * @returns true if it is, false otherwise
 */
bool Socket::isConnected()
{
	return connected ; // Opponenhandle is -1 if no connection is present
}

/**
 * Gives IP of connected opponent
 * @returns IP of connected opponent, NULL if none
 */
std::string Socket::getOpponent()
{
	if (!isConnected())
		return NULL ;
	return inet_ntoa(opponentsocket.sin_addr) ;
}
