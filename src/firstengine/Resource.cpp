#include "Resource.h"
#include "CacheManager.h"

namespace firstengine
{
	void Resource::load()
	{
		onLoad();
	}

	std::weak_ptr<Core> Resource::getCore()
	{
		return cache.lock()->getCore();
	}
}