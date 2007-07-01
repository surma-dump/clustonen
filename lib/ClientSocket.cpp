#include "ClientSocket.h"

/**
 * Creates a socket and connects it to a host
 * @param host Ip of the host to connect to
 * @param port Port on which to connect
 */
ClientSocket::ClientSocket(std::string host, int port)
{
	sockethandle = socket(AF_INET, SOCK_STREAM, 0) ; // Create socket
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
 * Closes the connection, if present, and destroys socket
 */
void ClientSocket::close()
{
	::close(sockethandle) ; // and after that yourself
}

/**
 * Sends a bytesequence to the connected host
 * @param msg bytesequence to send
 */
void ClientSocket::write(const char* msg, int len)
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
const char* ClientSocket::getMessage()
{
	return msg ;
}

/**
 * checks whether this socket is part of a connection
 * @returns true if it is, false otherwise
 */
bool ClientSocket::isConnected()
{
	return opponenthandle != -1 ; // Opponenhandle is -1 if no connection is present
}

/**
 * Gives IP of connected opponent
 * @returns IP of connected opponent, NULL if none
 */
std::string ClientSocket::getOpponent()
{
	if (opponenthandle == -1)
		return NULL ;
	return inet_ntoa(opponentsocket.sin_addr) ;
}
