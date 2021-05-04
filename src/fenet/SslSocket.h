#ifndef FENET_SSLSOCKET_H
#define FENET_SSLSOCKET_H

#include "SocketHandle.h"
#include "SocketOptions.h"
#include "IPVersion.h"
#include "FenetResult.h"
#include <openssl/ssl.h>

namespace fenet
{
	struct IPEndPoint;
	struct Packet;
	struct SSLSocket
	{
		SSLSocket(IPVersion ipVersion = IPVersion::IPv4, SocketHandle socketHandle = INVALID_SOCKET);
		FenetResult Create();
		FenetResult Close();

		FenetResult Bind(IPEndPoint endPoint);
		FenetResult Listen(IPEndPoint endPoint, int backLog = 5);
		FenetResult Accept(SSLSocket& o_Socket);
		FenetResult Connect(IPEndPoint endPoint);

		FenetResult SetSSLContext();

		FenetResult Send(const void* data, int numOfBytes, int& bytesSent);
		FenetResult Recieve(void* destination, int numOfBytes, int& bytesRecieved);
		FenetResult SendAll(const void* data, int numOfBytes);
		FenetResult RecieveAll(void* destination, int numOfBytes);

		FenetResult Send(Packet& packet);
		FenetResult Recieve(Packet& packet);

		FenetResult SetSocketOption(SocketOptions option, BOOL value);

		SocketHandle GetHandle();
		IPVersion GetIPVersion();

	private:
		FenetResult WrapSocketInSSL(SSLSocket& o_Socket);
		FenetResult DoneHandShake();
		bool handshake = false;
		IPVersion ipVersion = IPVersion::IPv4;
		SocketHandle socketHandle = INVALID_SOCKET;

		SSL* ssl;
		SSL_CTX* sslContext;

	};
}

#endif

