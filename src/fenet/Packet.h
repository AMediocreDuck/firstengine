#ifndef FENET_PACKET_H
#define FENET_PACKET_H

#ifndef WIN32_LEAN_AND_MEAN //Used to avoid conflicts of Winsock.h 
#define WIN32_LEAN_AND_MEAN
#endif
#include <vector>
#include <WinSock2.h>
#include <string>
#include <sstream>
#include "Exception.h"


namespace fenet
{
	struct Packet
	{
		Packet();
		void Clear();
		void Append(const void* data, uint32_t size);

		//Packet& operator << (uint32_t data);
		//Packet& operator >> (uint32_t & data);

		Packet& operator << (const std::string & data);
		Packet& operator >> (std::string & data);
		void setDataSize(uint32_t dataSize);
		template <typename T>
		Packet& operator << (T data)
		{
			std::stringstream tmp;
			tmp << data;
			std::stringstream ss;
			uint32_t size = tmp.str().size();
			if (size > 9999)
			{
				throw Exception("Too Much Data Begin Added into Packet at Once");

			}
			ss << size;
			if (size < 1000)
			{
				ss << "-";
				if (size < 100)
				{
					ss << "-";
					if (size < 10)
					{
						ss << "-";
					}
				}
			}
			ss << data;
			Append(ss.str().data(), ss.str().size());
			//*this << (uint32_t)data.size();
			//Append(data.data(), data.size());
			return *this;
		}

		template <typename T>
		Packet& operator >> (T &data)
		{
			uint32_t extractionOffset = 0;
			char dataSize[4] = { };
			uint32_t size = 0;
			if ((extractionOffset + sizeof(uint32_t)) > buffer.size())
			{
				throw Exception("Extraction Offset Exceeds the Buffer Size");
			}
			memcpy(&dataSize, &buffer[extractionOffset], sizeof(uint32_t));
			//memcpy(dataSize, *reinterpret_cast<uint32_t*>(&buffer[extractionOffset]), sizeof(uint32_t));
			//size = *reinterpret_cast<uint32_t*>(&buffer[extractionOffset]);
			extractionOffset += 4;
			std::stringstream tmp;
			for (int i = 0; i < 4; i++)
			{
				if (dataSize[i] == '-' || dataSize[i] ==  '\0')
				{
					break;
				}
				tmp << dataSize[i];
			}
			size = std::stoi(tmp.str());
			tmp.str(std::string());
			for (int j = 0; j < size; j++)
			{
				tmp << buffer[extractionOffset + j];
			}
			T tmpData;
			tmp >> tmpData;
			//tmpData = tmp.str();
			memcpy(&data, &tmpData, sizeof(tmpData));
			//data = static_cast<T*>(tmp);
			//memcpy(&data, &tmp, tmp.str().size());
			//uint32_t size = 0;
			//*this >> size;
			//intptr_t extractionOffset = 0;
			//if ((extractionOffset + size) > buffer.size())
			//{
			//	throw Exception("Extraction Offset Exceeds the Buffer Size");
			//}
			//std::string tmpString;
			//tmpString.resize(size);
			//memcpy(&tmpString, &buffer[0],size*sizeof(char));
			//tmp.clear();
			//tmp << &buffer[extractionOffset];
			////extractionOffset = *reinterpret_cast<uint32_t*>(&buffer[0]);
			//char tmp[5] = { 0 };
			//tmp[0] = buffer[0];
			////tmp[1] = buffer[1];
			////tmp[2] = buffer[2];
			////tmp[3] = buffer[3];
			//extractionOffset = atoi(tmp);
			//tmp.clear();
			//tmp.resize(size * sizeof(T));
			//memcpy(&tmp, &buffer[extractionOffset], size * sizeof(T));
			//data = *reinterpret_cast<uint32_t*>(&buffer[extractionOffset]);
			//data = ntohl(data);
			//data = *reinterpret_cast<T*>(&buffer[extractionOffset]);
			//data = ntohl(data);
			extractionOffset += size;
			return *this;
		}

		std::vector<char> buffer;
	private:
		//uint32_t extractionOffset;
		//Packet& operator >> (uint32_t& data);


	};
}
#endif