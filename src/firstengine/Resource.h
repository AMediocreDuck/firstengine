#ifndef FIRSTENGINE_RESOURCE_H
#define FIRSTENGINE_RESOURCE_H

#include <memory>
#include <string>
namespace firstengine
{
	struct Core;
	struct CacheManager;
	struct Resource
	{
		friend struct firstengine::CacheManager;
		void load();
		virtual void onLoad() {};
		std::weak_ptr<Core> getCore();

	protected:
		std::string path;
		std::weak_ptr<CacheManager> cache;
	};
}


#endif

