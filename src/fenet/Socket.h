#ifndef FENET_SOCKET_H
#define FENET_SOCKET_H

#include "SocketHandle.h"
#include "SocketOptions.h"
#include "IPVersion.h"
#include "FenetResult.h"


namespace fenet
{
	struct IPEndPoint;
	struct Packet;
	struct Socket
	{
		Socket(IPVersion ipVersion = IPVersion::IPv4, SocketHandle socketHandle = INVALID_SOCKET);
		FenetResult Create();
		FenetResult Close();

		FenetResult Bind(IPEndPoint endPoint);
		FenetResult Listen(IPEndPoint endPoint, int backLog);
		FenetResult Accept(Socket& o_Socket);
		FenetResult Connect(IPEndPoint endPoint);

		FenetResult Send(const void * data, int numOfBytes, int & bytesSent);
		FenetResult Recieve(void* destination, int numOfBytes, int& bytesRecieved);
		FenetResult SendAll(const void* data, int numOfBytes);
		FenetResult RecieveAll(void* destination, int numOfBytes);

		FenetResult Send(Packet &packet);
		FenetResult Recieve(Packet &packet);

		FenetResult SetSocketOption(SocketOptions option, BOOL value);


		SocketHandle GetHandle();
		IPVersion GetIPVersion();

	private:
		IPVersion ipVersion = IPVersion::IPv4;
		SocketHandle socketHandle = INVALID_SOCKET;

	};
}

#endif

