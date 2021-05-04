#include "Socket.h"
#include <iostream>
#include "IPEndPoint.h"
#include "Packet.h"
#include "Constants.h"

namespace fenet
{
	Socket::Socket(IPVersion ipVersion, SocketHandle socketHandle) :ipVersion(ipVersion), socketHandle(socketHandle)
	{

	}
	FenetResult Socket::Create()
	{

		//Checks to see if socket has already be created 
		if (socketHandle != INVALID_SOCKET)
		{
			std::cout << "Socket Already Created" << std::endl;
			return FenetResult::fenetSafeExit;
		}
		//Creates Socket as IPv4/IPv6 In the TCP Protocol
		if (ipVersion == IPVersion::IPv4)
		{
			socketHandle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		}
		else
		{
			socketHandle = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
		}

		if (socketHandle == INVALID_SOCKET)
		{
			int error = WSAGetLastError();
			{
				std::cout << "Socket Failed to be Created: " << error << std::endl;
				return FenetResult::fenetError;
			}
		}
		std::cout << "Socket Created Successfully" << std::endl;
		return FenetResult::fenetSuccess;
	}
	FenetResult Socket::Close()
	{
		if (socketHandle == INVALID_SOCKET)
		{
			std::cout << "No Open Socket Available" << std::endl;
			return FenetResult::fenetSafeExit;
		}

		int result = closesocket(socketHandle);
		if (result != 0) // Error occured 
		{
			int error = WSAGetLastError();
			std::cout << "Failed to Close Socket: " << error << std::endl;
			return FenetResult::fenetError;
		}
		std::cout << "Socket Closed Successfully" << std::endl;
		socketHandle = INVALID_SOCKET;
		return FenetResult::fenetSuccess;
	}
	FenetResult Socket::Bind(IPEndPoint endPoint)
	{
		int result = 0;
		if (ipVersion == IPVersion::IPv4)
		{
			sockaddr_in addr = endPoint.GetSockaddrIPv4();
			result = bind(socketHandle, (sockaddr*)(&addr), sizeof(sockaddr_in));
		}
		else
		{
			sockaddr_in6 addr = endPoint.GetSockaddrIPv6();
			result = bind(socketHandle, (sockaddr*)(&addr), sizeof(sockaddr_in6));
		}
		if (result != 0)
		{
			int error = WSAGetLastError();
			std::cout << "Could Not Bind Socket on Port: " << endPoint.GetPort() <<" Error Code: " << error << std::endl;
			return FenetResult::fenetError;
		}
		std::cout << "Socket Successfully Bound to Port: " << endPoint.GetPort() << std::endl;
		return FenetResult::fenetSuccess;
	}
	FenetResult Socket::Listen(IPEndPoint endPoint, int backLog)
	{
		if (ipVersion == IPVersion::IPv6)
		{
			if (SetSocketOption(SocketOptions::IPv6_Only, FALSE) != FenetResult::fenetSuccess)
			{
				return FenetResult::fenetSafeExit;
			}
		}

		if (Bind(endPoint) == FenetResult::fenetError)
		{
			return FenetResult::fenetError;
		}
		int result = listen(socketHandle, backLog);
		if (result != 0)
		{
			int error = WSAGetLastError();
			std::cout << "Socket Could Not Listen on Port: " << endPoint.GetPort() << " Error: " << error << std::endl;
			return FenetResult::fenetError;
		}
		std::cout << "Socket Successfully Listening on Port: " << endPoint.GetPort() << std::endl;
		return fenetSuccess;
	}

	FenetResult Socket::Accept(Socket& o_Socket)
	{
		if (ipVersion == IPVersion::IPv4)
		{
			sockaddr_in addr = {};
			int len = sizeof(sockaddr_in);
			SocketHandle acceptConhand = accept(socketHandle, (sockaddr*)(&addr), &len);
			if (acceptConhand == INVALID_SOCKET)
			{
				int error = WSAGetLastError();
				std::cout << "Accepting Socket Failed. Error: " << error << std::endl;
				return FenetResult::fenetError;
			}
			IPEndPoint newConEndPoint((sockaddr*)&addr);
			o_Socket = Socket(IPVersion::IPv4, acceptConhand);
			std::cout << "Connection Accepted" << std::endl;
			newConEndPoint.PrintInfo();
		}
		else
		{
			sockaddr_in6 addr = {};
			int len = sizeof(sockaddr_in6);
			SocketHandle acceptConhand = accept(socketHandle, (sockaddr*)(&addr), &len);
			if (acceptConhand == INVALID_SOCKET)
			{
				int error = WSAGetLastError();
				std::cout << "Accepting Socket Failed. Error: " << error << std::endl;
				return FenetResult::fenetError;
			}
			IPEndPoint newConEndPoint((sockaddr*)&addr);
			o_Socket = Socket(IPVersion::IPv6, acceptConhand);
			std::cout << "Connection Accepted" << std::endl;
			newConEndPoint.PrintInfo();
		}

		return FenetResult::fenetSuccess;
	}
	FenetResult Socket::Connect(IPEndPoint endPoint)
	{
		if (ipVersion != endPoint.GetIPVersion())
		{
			std::cout << "Socket IPVersion Does Not Match IPEndPoint IPVersion" << std::endl;
			return FenetResult::fenetError;
		}
		int result = 0;
		if (ipVersion == IPVersion::IPv4)
		{
			sockaddr_in addr = endPoint.GetSockaddrIPv4();
			result = connect(socketHandle, (sockaddr*)(&addr), sizeof(sockaddr_in));
		}
		else
		{
			sockaddr_in6 addr = endPoint.GetSockaddrIPv6();
			result = connect(socketHandle, (sockaddr*)(&addr), sizeof(sockaddr_in6));
		}

		if (result != 0)
		{
			int error = WSAGetLastError();
			std::cout << "Connecting Failed. Error: " << error << std::endl;
			return FenetResult::fenetError;
		}
		std::cout << "Successfully Connected." << std::endl;
		return FenetResult::fenetSuccess;
	}
	FenetResult Socket::Send(const void* data, int numOfBytes, int & bytesSent)
	{
		bytesSent = send(socketHandle, (const char*)data, numOfBytes, NULL);
		if (bytesSent == SOCKET_ERROR)
		{
			int error = WSAGetLastError();
			std::cout << "Failed to Send Data. Error: " << error << std::endl;
			return FenetResult::fenetError;
		}

		return FenetResult::fenetSuccess;
	}

	FenetResult Socket::Recieve(void* destination, int numOfBytes, int& bytesRecieved)
	{
		bytesRecieved = recv(socketHandle, (char*)destination, numOfBytes, NULL);
		if (bytesRecieved == 0)
		{
			std::cout << "Client has disconnected" << std::endl;
			return FenetResult::fenetSafeExit;
		}
		if (bytesRecieved == SOCKET_ERROR)
		{
			int error = WSAGetLastError();
			std::cout << "Failed to Recieve Data. Error: " << error << std::endl;
			return FenetResult::fenetError;
		}
		return fenetSuccess;
	}

	FenetResult Socket::SendAll(const void* data, int numOfBytes)
	{
		int totalBytesSent = 0;
		while (totalBytesSent < numOfBytes)
		{
			int bytesRemaining = numOfBytes - totalBytesSent;
			int bytesSent = 0;
			char* bufferOffset = (char*)data + totalBytesSent; //Use Char as its = to one byte
			FenetResult result = Send(bufferOffset, bytesRemaining, bytesSent);
			if (result != FenetResult::fenetSuccess)
			{
				return FenetResult::fenetError;
			}
			totalBytesSent += bytesSent;
		}
		return FenetResult::fenetSuccess;
	}

	FenetResult Socket::RecieveAll(void* destination, int numOfBytes)
	{
		int totalBytesRecieved = 0;
		while (totalBytesRecieved < numOfBytes)
		{
			int bytesRemaining = numOfBytes - totalBytesRecieved;
			int bytesRecieved = 0;
			char* bufferOffset = (char*)destination + totalBytesRecieved; //Use Char as its = to one byte
			FenetResult result = Recieve(bufferOffset, bytesRemaining, bytesRecieved);
			if (result != FenetResult::fenetSuccess)
			{
				return result;
			}
			totalBytesRecieved += bytesRecieved;
		}
		return FenetResult::fenetSuccess;
	}

	FenetResult Socket::Send(Packet& packet)
	{
		uint16_t encodedPacketSize = htons(packet.buffer.size());
		FenetResult result = SendAll(&encodedPacketSize, sizeof(uint16_t));
		if (result != FenetResult::fenetSuccess)
		{
			return FenetResult::fenetError;
		}
		result = SendAll(packet.buffer.data(), packet.buffer.size());
		if (result != FenetResult::fenetSuccess)
		{
			return FenetResult::fenetError;
		}
		return FenetResult::fenetSuccess;
	}

	FenetResult Socket::Recieve(Packet& packet)
	{
		packet.Clear();

		uint16_t encodedSize = 0;
		FenetResult result = RecieveAll(&encodedSize, sizeof(uint16_t));
		if (result != FenetResult::fenetSuccess)
		{
			return result;
		}
		uint16_t bufferSize = ntohs(encodedSize);
		if (bufferSize > g_MaxPacketSize)
		{
			std::cout << "Packet Size too Large to Recieve" << std::endl;
			return FenetResult::fenetError;
		}
		packet.buffer.resize(bufferSize);
		result = RecieveAll(&packet.buffer[0], bufferSize);
		if (result != FenetResult::fenetSuccess)
		{
			return FenetResult::fenetError;
		}
		return FenetResult::fenetSuccess;
	}

	FenetResult Socket::SetSocketOption(SocketOptions option, BOOL value)
	{
		int result;
		switch (option)
		{
		case SocketOptions::TCP_NoDelay:
		{
			std::cout << "Socket Option Change:TCP_NoDelay" << std::endl;
			result = setsockopt(socketHandle, IPPROTO_TCP, TCP_NODELAY, (const char*)&value, sizeof(value));
			break;
		}

		case SocketOptions::IPv6_Only:
		{
			std::cout << "Socket Option Change:IPv6_Only" << std::endl;
			result = setsockopt(socketHandle, IPPROTO_IPV6, IPV6_V6ONLY, (const char*)&value, sizeof(value));
			break;
		}

		default:
			std::cout << "No Suitable Option Detected" << std::endl;
			return FenetResult::fenetSafeExit;
		}

		if (result != 0)
		{
			int error = WSAGetLastError();
			std::cout << "Failed to Change Socket Options: " << error << std::endl;
			return FenetResult::fenetError;
		}
		std::cout << "Socket Option Change Successful" << std::endl;
		return FenetResult::fenetSuccess;
	}
	SocketHandle Socket::GetHandle()
	{
		return socketHandle;
	}

	IPVersion Socket::GetIPVersion()
	{
		return ipVersion;
	}
}