#include "Packet.h"
#include "Exception.h"
#include "Constants.h"

namespace fenet
{

	Packet::Packet()
	{
		Clear();
	}
	void Packet::Clear()
	{
		buffer.clear();
		//extractionOffset = 0;
	}

	void Packet::Append(const void* data, uint32_t size)
	{
		if ((buffer.size() + size) > g_MaxPacketSize)
		{
			throw Exception("Packet Exceeds the Max Size Limit");
		}

		buffer.insert(buffer.end(), (char*)data, (char*)data + size);
	}

	//Packet& Packet::operator<<(uint32_t data)
	//{
	//	data = htonl(data);
	//	Append(&data, sizeof(uint32_t));
	//	return *this;
	//}

	//Packet& Packet::operator>>(uint32_t& data)
	//{
	//	uint32_t extractionOffset = 0;
	//	if ((extractionOffset + sizeof(uint32_t)) > buffer.size())
	//	{
	//		throw Exception("Extraction Offset Exceeds the Buffer Size");
	//	}
	//	data = *reinterpret_cast<uint32_t*>(&buffer[extractionOffset]);
	//	data = ntohl(data);
	//	extractionOffset += sizeof(uint32_t);
	//	return *this;
	//}

	Packet& Packet::operator<<(const std::string & data)
	{
		//data = htonl(data);
		uint32_t size = data.size();
		std::string numStr;
		numStr.resize(sizeof(uint32_t));
		numStr = std::to_string(size);
		if (numStr.size() > 9999)
		{
			throw Exception("Too Much Data Begin Added into Packet at Once");
		}
		char tmpSize[5] = { };
		strcpy(tmpSize, numStr.c_str());
		Append(&tmpSize, sizeof(uint32_t));
		//*this << (uint32_t)data.size();
		Append(data.data(), data.size());
		return *this;
	}

	Packet& Packet::operator>>(std::string& data)
	{
		uint32_t extractionOffset = 0;
		char tmpSize[5] = {};
		uint32_t tmpIntSize;
		if ((extractionOffset + sizeof(uint32_t)) > buffer.size())
		{
			throw Exception("Extraction Offset Exceeds the Buffer Size");
		}

		for (int i = 0; i < 5; i++)
		{
			if (buffer[i] == '\0')
			{
				break;
			}
			tmpSize[i] = buffer[i];
		}
		tmpIntSize = atoi(tmpSize);
		extractionOffset += 4;
		//tmpStringSize.append(buffer.begin(), buffer.begin() + 4);
		


		//data = *reinterpret_cast<uint32_t*>(&buffer[extractionOffset]);
		//data = ntohl(data);
		//extractionOffset += sizeof(uint32_t);

		data.clear();
		//uint32_t stringSize = 0;
		//this >> stringSize;

		if ((extractionOffset + tmpIntSize) > buffer.size())
		{
			throw Exception("Extraction Offset Exceeds the Buffer Size");
		}

		data.resize(tmpIntSize);
		data.assign(&buffer[extractionOffset], tmpIntSize);
		extractionOffset += tmpIntSize;

		std::vector<char>::iterator it = buffer.begin();
		buffer.erase(it, it + extractionOffset);
		return *this;
	}

	void Packet::setDataSize(uint32_t dataSize)
	{

	}

}
