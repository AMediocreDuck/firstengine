#ifndef FIRSTENGINE_CACHEMANAGER_H
#define FIRSTENGINE_CACHEMANAGER_H

#include <memory>
#include <vector>
#include <iostream>
namespace firstengine
{
	struct Core;
	struct Resource;
	/********************************************//**
	*  \brief Inbuilt Cache Store for Resource 
	***********************************************/
	struct CacheManager
	{
		friend struct firstengine::Core;
		//template <typename T>
		//std::shared_ptr<T> createResource()
		//{
		//	std::shared_ptr<T> rtn = std::make_shared<T>();
		//	rtn->cache = self;
		//	rtn->onInitialize();
		//	return rtn;
		//}

		/********************************************//**
		* \brief Template function to load and add resources into cache
		*
		* Takes the directory path to a file as its input 
		*
		* Iterates through all loaded resources and compares their paths with the input path.
		*
		* If paths match this resource has already been loaded and a pointer to it is returned.
		*
		* If no match is found a new resource is made and added to the cache before being returned.
		***********************************************/
		template <typename T>
		std::shared_ptr<T> loadResource(const char* path)
		{

			for (size_t ri = 0; ri < resources.size(); ri++)
			{
				
				if (resources.at(ri)->path == path)
				{
					std::shared_ptr<T> rtn = std::dynamic_pointer_cast<T>(resources.at(ri));
					std::cout << "Resource Loaded From Cache" << std::endl;
					return rtn;
				}
			}
				std::shared_ptr<T> rtn = std::make_shared<T>();
				rtn->cache = self;
				rtn->path = path;
				rtn->onLoad();
				resources.push_back(rtn);
				std::cout << "New Resource Loaded" << std::endl;
				return rtn;
		}
		/********************************************//**
		* \brief Returns pointer to core 
		***********************************************/
		std::shared_ptr<Core> getCore() { return core.lock(); };
	private:
		std::weak_ptr<CacheManager> self;
		std::weak_ptr<Core> core;
		std::vector<std::shared_ptr<Resource>> resources;
	};
}



#endif 
