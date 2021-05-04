#ifndef FENET_NETWORK_H
#define FENET_NETWORK_H

#ifndef WIN32_LEAN_AND_MEAN //Used to avoid conflicts of Winsock.h 
#define WIN32_LEAN_AND_MEAN
#endif
#include <WinSock2.h>
#include "FenetResult.h"

namespace fenet
{
	struct Network 
	{
		static FenetResult Initialize();
		static void Shutdown();

		private:


	};
}

#endif
