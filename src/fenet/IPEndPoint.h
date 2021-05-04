#ifndef FENET_IPENDPOINT_H
#define FENET_IPENDPOINT_H

#include <WS2tcpip.h>
#include "IPVersion.h"
#include <vector>
#include <string>

namespace fenet
{
	struct IPEndPoint
	{
		IPEndPoint(const char* _ip, unsigned short _port);
		IPEndPoint(sockaddr * addr);
		IPVersion GetIPVersion();
		std::string GetHostName();
		std::string GetIPString();
		std::vector<uint8_t> GetIPBytes();
		unsigned short GetPort();
		sockaddr_in GetSockaddrIPv4();
		sockaddr_in6 GetSockaddrIPv6();

		void PrintInfo();
	private:
		IPVersion ipVersion = IPVersion::Unknown;
		std::string hostName = "";
		std::string ipString = "";
		std::vector<uint8_t> ipBytes;
		unsigned short port;
	};
}

#endif