

#include "firstengine/NetworkManager.h"
#include "firstengine/Entity.h"
#include "firstengine/Core.h"
#include "firstengine/ThreadManager.h"
#include "firstengine/Socket.h"

#include <functional>

namespace firstengine
{
	void NetworkManager::onInitialize(IPVersion _ipVersion, bool _server )
	{
		if (getCore()->networkManager == nullptr)
		{
			Network = std::make_shared<fenet::Network>();
			FenetResult result;
			result = Network->Initialize();
			if (result != FenetResult::fenetSuccess)
			{
				throw firstengine::Exception("Failed to Initialize Fenet");
			}
			std::shared_ptr<NetworkManager> self = getEntity()->getComponent<NetworkManager>();
			getCore()->networkManager = self;

		}
		else
		{
			throw firstengine::Exception("Network Manager Already Exists");
		}

		threadManager = getCore()->threadManager;
		ipVersion = _ipVersion;
		server = _server;
		socketsMutex = threadManager.lock()->createMutex(1);
	}

	std::shared_ptr<firstengine::Socket> NetworkManager::createSocket()
	{
		std::shared_ptr<firstengine::Socket> tmp = std::make_shared<firstengine::Socket>(ipVersion);
		tmp->Create();
		tmp->core = getCore();
		tmp->socketMutex = threadManager.lock()->createMutex(socketCount);
		tmp->socketID = socketCount;
		socketCount += 1;
		if (server)
		{
			sockets.push_back(tmp);
		}
		else
		{
			socket = tmp;
		}
		return tmp;
	}
	std::shared_ptr<firstengine::Mutex> NetworkManager::getSocketMutex()
	{
		return socketsMutex;
	}
	std::shared_ptr<firstengine::Socket> NetworkManager::createTCPListenSock()
	{
		tcpListener = std::make_shared<Socket>();
		tcpListener->Create();
		return tcpListener;
	}
	void NetworkManager::Listen(const char* _ipAddress, int _port, int _backLog)
	{
		fenet::IPEndPoint tmpEndPoint(_ipAddress, _port);
		listening = true;
		std::function<void(IPEndPoint, int )> onListenFunc = std::bind(&NetworkManager::onListen, this, std::placeholders::_1, std::placeholders::_2);
		threadManager.lock()->createThread(onListenFunc, tmpEndPoint, _backLog);
		//onListen();

	}
	void NetworkManager::onListen(IPEndPoint _ipEndPoint, int _backLog)
	{
		if (tcpListener->Listen(_ipEndPoint, _backLog))
		{	
			//socketsMutex = threadManager.lock()->createMutex(1);
			while (listening)
			{
				//socketsMutex->mutex.lock();
				std::shared_ptr<firstengine::Socket> tmpSock = createSocket();
				if (tcpListener->Accept(tmpSock))
				{
					//socketsMutex->mutex.unlock();
					std::function<void()> recvLoop = std::bind(&Socket::recieveLoop, tmpSock.get());
					threadManager.lock()->createThread(recvLoop);

				}
			}
		}
		else
		{
			listening = false;
		}
		tcpListener->Close();
	}

	std::shared_ptr<firstengine::Socket> NetworkManager::getSocket(int _Id)
	{
		if (server)
		{
			for (std::vector<std::shared_ptr<firstengine::Socket>>::iterator it = sockets.begin(); it != sockets.end(); ++it)
			{
				if (it->get()->socketID == _Id)
				{
					return *it;
				}
			}
			throw firstengine::Exception("Socket Could not be Found");
		}
		else
		{
			return socket;
		}
	}	

	void firstengine::NetworkManager::CloseAllSockets()
	{
		if (server)
		{			
			socketsMutex->mutex.lock();
			for (std::vector<std::shared_ptr<firstengine::Socket>>::iterator it = sockets.begin(); it != sockets.end();)
			{
				it->get()->Close();
				it = sockets.erase(it);
			}			

			listening = false;
			tcpListener->Close();
			socketsMutex->mutex.unlock();
		}
		else
		{
			socket->Close();
		}
	}

	void NetworkManager::CleanUp()
	{

		CloseAllSockets();
		Network->Shutdown();
		threadManager.lock()->shutDownThreads();
	}
}