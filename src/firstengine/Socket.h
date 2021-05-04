#ifndef FIRSTENGINE_SOCKET_H
#define FIRSTENGINE_SOCKET_H


#include "fenet/Fenet.h"
#include <memory>

#include "firstengine/Core.h"
#include "ThreadManager.h"

namespace firstengine
{
	struct Packet;


	struct Socket
	{
		Socket();
		~Socket();
		Socket(fenet::IPVersion _ipVersion);
		void Close();
		bool Create();
		bool Listen(fenet::IPEndPoint endPoint, int backLog = 5);
		bool Accept(std::weak_ptr<Socket> o_Socket);
		bool Connect(fenet::IPEndPoint endPoint);
		virtual void onConnect() ;

		bool Send(std::shared_ptr<Packet> _packet);
		bool Recieve();
		virtual void onRecieve(std::shared_ptr<firstengine::Packet> _outPacket);


		void Disconnect();
		virtual void onDisconnect() ;

		std::shared_ptr<fenet::Socket> GetSocket();
		bool GetRecvPacket(std::shared_ptr<firstengine::Packet>& _o_Packet);
		std::shared_ptr<firstengine::Mutex> getMutex();

	private:
		friend struct firstengine::NetworkManager;
		std::shared_ptr<fenet::Socket> socket;
		std::vector<std::shared_ptr<firstengine::Packet>> recvPacket;
		int socketID = 0;
		IPVersion ipVersion = IPv4;
		std::weak_ptr<firstengine::Core> core;
		std::shared_ptr<firstengine::Mutex> socketMutex;
		void recieveLoop();

		
	};

}
#endif