#include "Network.h"
#include <iostream>
#include <openssl/ssl.h>

namespace fenet
{
	FenetResult Network::Initialize()
	{
		WSADATA wsaData;
		// Initialize Winsock
		int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0) {
			std::cout << "WSAStartup failed:" << iResult << std::endl;
			return FenetResult::fenetError;
		}

		if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
		{
			std::cout << "Failed to find suitable version of Winsock:" << std::endl;
			return FenetResult::fenetError;
		}
		SSL_library_init();
		SSL_load_error_strings();

		std::cout << "Fenet Initialized Successfully!" << std::endl;
		return FenetResult::fenetSuccess;
	}
	void Network::Shutdown()
	{
		WSACleanup();
	}
}