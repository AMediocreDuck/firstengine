#ifndef FIRSTENGINE_PACKET_H
#define FIRSTENGINE_PACKET_H


#include "fenet/Fenet.h"
#include <memory>


namespace firstengine
{
	struct fenet::Packet;
	struct Packet
	{
		Packet();

		template<typename T>
		void addData(T data)
		{
			packet << data;
			dirty = true;
		}
		template<typename T>
		void retrieveData(T& data )
		{
			packet >> data;
		}
		void addData(const std::string& data);
		void retrieveData(std::string& data);

		fenet::Packet* getPacket();
	private:
		fenet::Packet packet;
		bool dirty;
	};

}
#endif