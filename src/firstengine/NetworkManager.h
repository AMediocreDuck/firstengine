#ifndef FIRSTENGINE_NetworkManager_H
#define FIRSTENGINE_NetworkManager_H


#include <vector>
#include <memory>
#include <mutex>

#include "firstengine/Component.h"
#include "fenet/Fenet.h"

#include "firstengine/ThreadManager.h"

namespace firstengine
{
	struct Socket;
	struct fenet::Network;

	struct NetworkManager : public Component
	{
		/********************************************//**
		* \brief Function called during creation
		***********************************************/
		void onInitialize(IPVersion _ipVersion, bool _server);
		/********************************************//**
		* \brief Ticks after all Entities have finished their tick()
		***********************************************/
		//void onAfterTick();
		std::shared_ptr<firstengine::Socket> createSocket();
		std::shared_ptr<firstengine::Mutex> getSocketMutex();


		bool listening = false;
		std::shared_ptr<firstengine::Socket> createTCPListenSock();
		void Listen(const char* _ipAddress, int _port, int _backLog);
		void onListen(IPEndPoint _ipEndPoint, int _backLog);
		std::shared_ptr<firstengine::Socket> getSocket(int _Id);


		//std::shared_ptr<firstengine::Socket> getSocket();

		void CloseAllSockets();
		void CleanUp();

	
	private:
		bool server = false;
		std::vector<std::shared_ptr<firstengine::Socket>> sockets;
		std::shared_ptr<firstengine::Socket> tcpListener;
		//std::shared<Socket> udpListener;
		std::shared_ptr<Socket> socket;
		int socketCount = 1000;
		IPVersion ipVersion;
		std::weak_ptr<firstengine::ThreadManager> threadManager;
		std::shared_ptr<fenet::Network> Network;
		std::shared_ptr<firstengine::Mutex> socketsMutex;
	};

}
#endif

