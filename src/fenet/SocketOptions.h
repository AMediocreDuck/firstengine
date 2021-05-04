#ifndef FENET_SOCKETOPTIONS_H
#define FENET_SOCKETOPTIONS_H

namespace fenet
{
	enum SocketOptions 
	{
		TCP_NoDelay, //True = Disables Nagle's Algorithm
		IPv6_Only // True = ONLY IPv6 False = Both IPv4 and IPv6 
	};
}

#endif
