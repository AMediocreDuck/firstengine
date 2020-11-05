#ifndef FIRSTENGINE_CACHEMANAGER_H
#define FIRSTENGINE_CACHEMANAGER_H

#include <memory>
#include <vector>

namespace firstengine
{
	struct Core;
	struct Resource;
	struct CacheManager
	{
		friend struct Core;
		//template <typename T>
		//std::shared_ptr<T> createResource()
		//{
		//	std::shared_ptr<T> rtn = std::make_shared<T>();
		//	rtn->cache = self;
		//	rtn->onInitialize();
		//	return rtn;
		//}

		template <typename T>
		std::shared_ptr<T> loadResource(const char* path)
		{

			for (size_t ri = 0; ri < resources.size(); ri++)
			{
				if (resources.at(ri)->path.c_str() == path)
				{
					std::shared_ptr<T> rtn = std::dynamic_pointer_cast<T>(resources.at(ri));
					return rtn;
				}
			}
				std::shared_ptr<T> rtn = std::make_shared<T>();
				rtn->cache = self;
				rtn->path = path;
				rtn->onLoad();
				resources.push_back(rtn);
				return rtn;
		}
	private:
		std::weak_ptr<CacheManager> self;
		std::weak_ptr<Core> core;
		std::vector<std::shared_ptr<Resource>> resources;
	};
}



#endif 
