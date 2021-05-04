#include "firstengine/Packet.h"
#include "fenet/Fenet.h"


namespace firstengine
{
	Packet::Packet()
	{

	}
	void Packet::addData(const std::string& data)
	{
		packet << data;
	}

	void Packet::retrieveData(std::string& data)
	{
		packet >> data;
	}

	fenet::Packet* Packet::getPacket()
	{
		return &packet;
	}

}