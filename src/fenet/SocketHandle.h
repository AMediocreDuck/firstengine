#ifndef FENET_SOCKETHANDLE_H
#define FENET_SOCKETHANDLE_H

#ifndef WIN32_LEAN_AND_MEAN //Used to avoid conflicts of Winlock.h 
#define WIN32_LEAN_AND_MEAN
#endif
#include <WinSock2.h>

namespace fenet
{
	//Add Cross platform stuff later on maybe 
	typedef SOCKET SocketHandle; 
}

#endif
