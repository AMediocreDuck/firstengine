#ifndef FIRSTENGINE_RESOURCE_H
#define FIRSTENGINE_RESOURCE_H

#include <memory>
#include <string>
namespace firstengine
{
	struct CacheManager;
	struct Resource
	{
		friend struct CacheManager;
		void load();
		virtual void onLoad() {};

	protected:
		std::string path;
		std::weak_ptr<CacheManager> cache;
	};
}


#endif

