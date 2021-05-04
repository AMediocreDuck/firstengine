#include "firstengine/firstEngine.h"
//#include "fenet/Fenet.h"
#include <cstdlib>
#include <iostream>
#include <memory>

//int main()
//{
//	if(Network::Initialize() == FenetResult::fenetSuccess)
//	{
//		Socket socket(IPVersion::IPv6);
//		if (socket.Create() == FenetResult::fenetSuccess)
//		{
//			if (socket.Listen(IPEndPoint("::", 4790)) == FenetResult::fenetSuccess) // 0.0.0.0 Means anything can connect
//			{
//				Socket newConnection;
//				if (socket.Accept(newConnection) == FenetResult::fenetSuccess)
//				{
//					Packet packet;
//					std::string string1 = "";
//					uint32_t int2 = 0;
//					std::string string3 = "Recieved: ";
//					char char4;
//					int result = FenetResult::fenetSuccess;
//					while (result == FenetResult::fenetSuccess)
//					{
//						//uint32_t bufferSize = 0;
//						result = newConnection.Recieve(packet);
//						if (result != FenetResult::fenetSuccess) { break; }
//
//						//bufferSize = ntohl(bufferSize);
//						if (packet.buffer.size() > g_MaxPacketSize)
//						{
//							break;
//						}
//						packet >> string3 >> string1 >> int2;
//						std::cout << string3 << string1 << int2 << std::endl;
//
//						//packet.Clear();
//						//packet << string3 << string1 << int2;
//						//result = newConnection.Send(packet);
//					
//					}
//
//					newConnection.Close();
//				}
//			}
//			if (socket.SetSocketOption(SocketOptions::TCP_NoDelay, TRUE) != FenetResult::fenetSuccess)
//			{
//
//			}
//			socket.Close();
//		}
//	}
//	fenet::Network::Shutdown();
//	system("pause");
//	return 0;
//
//}

int main()
{
	std::shared_ptr<Core> core = Core::initialize();
	std::shared_ptr<Entity> networkManager = core->addEntity();
	std::shared_ptr<ThreadManager> tm = networkManager->addComponent<ThreadManager>();
	std::shared_ptr<NetworkManager> nm = networkManager->addComponent<NetworkManager>(IPVersion::IPv4, true);

	std::shared_ptr<firstengine::Socket> tcpListen = nm->createTCPListenSock();//IPVersion::IPv6);
	nm->Listen("::", 27050, 5);


	int go;
	std::cin >> go;
	std::shared_ptr<firstengine::Socket> newConnection = nm->getSocket(1000);
	std::shared_ptr<firstengine::Mutex> socketMutex = newConnection->getMutex();
	std::string string1 = "";
	uint32_t int2 = 0;
	std::string string3 = "";
	char char4;
	bool result = true;
	std::shared_ptr<firstengine::Packet> packet1 = std::make_shared<firstengine::Packet>();
	int i = 1;
	while ( i > 0 )
	{

		//result = newConnection->Recieve();
		//if (result != FenetResult::fenetSuccess) { break; }

		//if (packet.buffer.size() > g_MaxPacketSize)
		//{
		//	break;
		//}
		//packet >> string3 >> string1 >> int2;
		std::cin >> i;
		socketMutex->mutex.lock();
		if (newConnection->GetRecvPacket(packet1))
		{
			packet1->retrieveData(string3);
			packet1->retrieveData(string1);
			packet1->retrieveData(int2);
			std::cout << string3 << string1 << int2 << std::endl;
		}
		socketMutex->mutex.unlock();
		//packet.Clear();
		//packet << string3 << string1 << int2;
		//result = newConnection.Send(packet);

	}
	nm->CleanUp();
	int stop;
	std::cin >> stop;
	return 0;

}





/*
if (socket.Create() == FenetResult::fenetSuccess)
	{
		if (socket.Listen(IPEndPoint("::", 27050))) // 0.0.0.0 Means anything can connect
		{
			std::shared_ptr<firstengine::Socket> newConnection = std::make_shared<firstengine::Socket>(IPVersion::IPv4);
			newConnection->Create();
			if (socket.Accept(newConnection) == FenetResult::fenetSuccess)
			{
				std::string string1 = "";
				uint32_t int2 = 0;
				std::string string3 = "";
				char char4;
				bool result = true;
				std::shared_ptr<firstengine::Packet> packet1 = std::make_shared<firstengine::Packet>();
				while (result )
				{

					result = newConnection->Recieve();
					if (result != FenetResult::fenetSuccess) { break; }

					//if (packet.buffer.size() > g_MaxPacketSize)
					//{
					//	break;
					//}
					//packet >> string3 >> string1 >> int2;
					packet1 = newConnection->GetRecvPacket();
					packet1->retrieveData(string3);
					packet1->retrieveData(string1);
					packet1->retrieveData(int2);
					//newConnection->recvPacket[0]->retrieveData(int2);
					std::cout << string3 << string1 << int2 << std::endl;

					//packet.Clear();
					//packet << string3 << string1 << int2;
					//result = newConnection.Send(packet);

				}

				newConnection->Close();
			}
		}
		//if (socket.SetSocketOption(SocketOptions::TCP_NoDelay, TRUE) != FenetResult::fenetSuccess)
		//{

		//}
		socket.Close();
	}
	nm->CleanUp();
	int stop;
	std::cin >> stop;
	return 0;
	*/








/*
#ifndef WIN32_LEAN_AND_MEAN //Used to avoid conflicts of Winlock.h 
#define WIN32_LEAN_AND_MEAN
#endif

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_PORT "27015"

//int main()
//{
//	WSAData wsaData;
//	int winResult; //Result varibales are used to validate the returns of Winsock functions
//
//	// Initialize Winsock, makes sure WS2_32.dll is initiated properly inorder for the program to fucntion
//	winResult = WSAStartup(MAKEWORD(2, 2), &wsaData); //MAKEWORD(2,2) get the version of WinSock
//	if (winResult != 0) {
//		printf("WSAStartup failed: %d\n", winResult);
//		return 0;
//	}
//
//	//Create a Socket
//	SOCKET listeningSock = socket(AF_INET, SOCK_DGRAM, 0); //SOCK_STREAM for TCP SOCK_DGRAM UDP
//	if (listeningSock == INVALID_SOCKET)
//	{
//		std::cout << "Socket Creation Failed" << std::endl;
//		WSACleanup();
//		return 0;
//	}
//
//	//Bind socket, port and IP address together
//	sockaddr_in hint;
//	hint.sin_family = AF_INET;
//	hint.sin_port = htons(27015);
//	hint.sin_addr.S_un.S_addr = INADDR_ANY; //Could also use inet_pton
//
//	int bindResult;
//	bindResult = bind(listeningSock, (sockaddr*)&hint, sizeof(hint));
//	if (bindResult == SOCKET_ERROR) {
//		printf("Bind failed with error: %d\n", WSAGetLastError());
//		closesocket(listeningSock);
//		WSACleanup();
//		return 0;
//	}
//
//	//Start the Listening 
//	int listenResult;
//	listenResult = listen(listeningSock, SOMAXCONN);
//	if (listenResult == SOCKET_ERROR) {
//		std::cout << ("Listen failed with error: %ld\n", WSAGetLastError());
//		closesocket(listeningSock);
//		WSACleanup();
//		return 0;
//	}
//
//	//Wait for Connection 
//	sockaddr_in client;
//	int clientSize = sizeof(client);
//	SOCKET cSock = accept(listeningSock, (sockaddr*)&client, &clientSize);
//	if (cSock == INVALID_SOCKET)
//	{
//		std::cout << ("Failed to accept client: %ld\n", WSAGetLastError());
//		closesocket(cSock);
//	}
//
//	char host[NI_MAXHOST]; // Clients remote name 
//	char service[NI_MAXHOST]; // Service (Port) the client is connected on
//
//	memset(host, 0, NI_MAXHOST); //ZeroMemory(host, NI_MAXHOST) for Windows, memset for Portability
//	memset(service, 0, NI_MAXSERV);
//
//	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
//	{
//		std::cout << host << " connected on port " << service << std::endl;
//	}
//	else
//	{
//		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
//		{
//			std::cout << host << " connected on port " << ntohs(client.sin_port) << std::endl;
//		}
//	}
//
//	//Cleanup listeningSocket
//	closesocket(listeningSock);
//
//	//Loop that talks to clients
//	int recvBuffLen = 512;
//	char recvBuf[512];
//	while (true)
//	{
//		memset(recvBuf, 0, recvBuffLen);
//
//		//Wait for Client to send Data
//		int bytesRecv = recv(cSock, recvBuf, recvBuffLen, 0);
//		if (bytesRecv == SOCKET_ERROR)
//		{
//			std::cout << "Error Recieving Data" << std::endl;
//			break;
//		}
//		if (bytesRecv == 0)
//		{
//			std::cout << "Client Disconnected" << std::endl;
//			break;
//		}
//
//		// Echo back to client
//		int sendResult;
//		sendResult = send(cSock, recvBuf, bytesRecv + 1, 0);
//		if (sendResult == SOCKET_ERROR) {
//			std::cout << ("send failed: %d\n", WSAGetLastError());
//			closesocket(cSock);
//			WSACleanup();
//			return 0;
//		}
//
//	}
//
//	//Cleanup Socket
//	closesocket(cSock);
//
//	//Clean WinSock
//	WSACleanup();
//
//}

//int __cdecl main(int argc, char** argv)
int main()
{
	//Setting up
	WSADATA wsaData;
	int iResult = NULL;
	SOCKET ListenSocket = INVALID_SOCKET; // Declaring the Socket
	struct addrinfo* result = NULL,
		* ptr = NULL,
		hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 0; //IPPROTO_TCP
	hints.ai_flags = AI_PASSIVE;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}


	// Resolve the local address and port to be used by the server
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	// Create a SOCKET for the server to listen for client connections
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) { //Error checking to make sure its a valid socket
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	//BINDING SOCKET
	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen); //Binds the Listening Socket to be used
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	//address data has now been binded so data can be freed up
	freeaddrinfo(result);

	//LISTENING ON SOCKET
	if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR) {
		printf("Listen failed with error: %ld\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	//ACCEPTING A CONNECTION
	SOCKET ClientSocket; //Temp Socket Object for accepting connections from client
	//Normally Multiple sockets are listening for connections from multiple clients using Multithreading
	ClientSocket = INVALID_SOCKET;

	// Accept a client socket
	ClientSocket = accept(ListenSocket, NULL, NULL); // ClientSocket set by accepting incomming connection
	if (ClientSocket == INVALID_SOCKET) {
		printf("accept failed: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	//Normally this is now passed off to a Worker thread to allow for more connections to be accepted

	//SENDING AND RECIEVING DATA
	int recvbuflen = 512;
	char recvbuf[512];
	int iSendResult; //int iResult as well but already declared above
	// Receive until the peer shuts down the connection
	do {

		iResult = recv(ClientSocket, recvbuf, recvbuflen, 0); //Recieves data from the ClientSocket
		if (iResult > 0) {
			printf("Bytes received: %d\n", iResult); //Prints the data recieved
			printf(recvbuf);
			printf("\n");

			// Echo the buffer back to the sender
			iSendResult = send(ClientSocket, recvbuf, iResult, 0); //Pings data back to client
			if (iSendResult == SOCKET_ERROR) {
				printf("send failed: %d\n", WSAGetLastError());
				closesocket(ClientSocket);
				WSACleanup();
				return 1;
			}
			printf("Bytes sent: %d\n", iSendResult);
		}
		else if (iResult == 0) //Client Disconnecting
			printf("Connection closing...\n");
		else { //Error sending data
			printf("recv failed: %d\n", WSAGetLastError());
			closesocket(ClientSocket);
			WSACleanup();
			return 1;
		}

	} while (iResult > 0); //loops until client DCS

	//DISCONNECTING SERVER
	// shutdown the send half of the connection since no more data will be sent
	iResult = shutdown(ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed: %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		WSACleanup();
		return 1;
	}
	// cleanup
	closesocket(ClientSocket);
	WSACleanup();

	return 0;
}
*/