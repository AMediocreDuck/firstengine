#include "firstengine/Socket.h"
#include "firstengine/exception.h"
#include "firstengine//Packet.h"
#include "fenet/Fenet.h"



namespace firstengine
{
	Socket::Socket() {}
	Socket::~Socket(){}
	Socket::Socket(fenet::IPVersion _ipVersion)
	{
		//playerID = _playerID;
		//sendPacket = std::make_shared<firstengine::Packet>();
	}

	void Socket::Close()
	{
		socket->Close();
	}

	bool Socket::Create()
	{
		std::shared_ptr<fenet::Socket> tmpSock = std::make_shared<fenet::Socket>(ipVersion);
		socket = tmpSock;
		socket->Create();
		return true;
	}

	bool Socket::Listen(fenet::IPEndPoint endPoint, int backLog )
	{
		if (socket->Listen(endPoint, backLog) != FenetResult::fenetSuccess)
		{
			return false;
		}
		return true;
	}
	bool Socket::Accept(const std::weak_ptr<Socket> o_Socket)
	{
		//fenet::Socket* tmpSock = o_Socket.lock()->GetSocket().get();
		//fenet::Socket tmpSock = *(o_Socket.lock()->GetSocket().get());
		if (socket->Accept(*(o_Socket.lock()->GetSocket().get())) != FenetResult::fenetSuccess)
		{
			return false;
		}
		onConnect();
		return true;
	}
	bool Socket::Connect(fenet::IPEndPoint endPoint)
	{
		if (socket->Connect(endPoint) != FenetResult::fenetSuccess)
		{
			return false;
		}
		
		onConnect();
		return true;
	}

	void Socket::onConnect()
	{
	}

	bool Socket::Send(std::shared_ptr<Packet> _packet)
	{
		//fenet::Packet* pktPtr = sendPacket->getPacket();
		fenet::Packet* pktPtr = _packet->getPacket();
		FenetResult result = socket->Send(*pktPtr);
		//FenetResult result = socket->Send(sendPacket->getPacket());
		if(result == FenetResult::fenetError)
		{
			throw firstengine::Exception("Failed to Send Data");
		}
		return true;
	}


	bool Socket::Recieve()
	{
		std::shared_ptr<firstengine::Packet> tmpPack = std::make_shared<firstengine::Packet>();
		FenetResult result = socket->Recieve(*tmpPack->getPacket());

		//fenet::Packet* pktPtr = recvPacket->getPacket();
		//fenet::Packet temp;
		//FenetResult result = socket->Recieve(*pktPtr);
		//pktPtr->buffer.resize(temp.buffer.size(), '0');
		//pktPtr->buffer = temp.buffer;
		//memcpy(&(pktPtr->buffer), &temp.buffer[0], temp.buffer.size());
		//std::string str(temp.buffer.begin(), temp.buffer.end());
		//recvPacket->getPacket().buffer.resize(temp.buffer.size() * sizeof(char), '0');
		//recvPacket->getPacket().buffer = temp.buffer;
		//memcpy(&(recvPacket->getPacket().buffer[0]), &str, str.size());
		//recvPacket->addData(str);
		if (result == FenetResult::fenetError)
		{
			throw firstengine::Exception("Failed to Recieve Data");
		}
		if (result == FenetResult::fenetSafeExit)
		{
			Disconnect();
			return false;
		}
		socketMutex->mutex.lock();
		recvPacket.push_back(tmpPack);
		socketMutex->mutex.unlock();
		onRecieve(tmpPack);
		return true;
	}

	void Socket::onRecieve(std::shared_ptr<firstengine::Packet> _outPacket)
	{
	}


	void Socket::Disconnect()
	{
		onDisconnect();
	}

	void Socket::onDisconnect()
	{
	}

	std::shared_ptr<fenet::Socket> Socket::GetSocket()
	{
		return socket;
	}

	bool Socket::GetRecvPacket(std::shared_ptr<firstengine::Packet>& _o_Packet)
	{
		if (recvPacket.size() == 0)
		{
			return false;
		}
		_o_Packet = recvPacket[0];
		recvPacket.erase(recvPacket.begin());
		return true;
	}

	std::shared_ptr<firstengine::Mutex> Socket::getMutex()
	{
		return socketMutex;
	}

	void Socket::recieveLoop()
	{
		bool result = true;
		while (result)
		{

			result = Recieve();
			if (result != true) { break; }

		}
	}



}