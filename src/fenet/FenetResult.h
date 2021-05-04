#ifndef FENET_FENETRESULT_H
#define FENET_FENETRESULT_H

#include "SocketHandle.h"

namespace fenet
{
	enum FenetResult
	{
		fenetSuccess = 1,
		fenetError,
		fenetNotYetImplemented,
		fenetSafeExit
	};
}

#endif

