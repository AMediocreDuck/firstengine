#ifndef FIRSTENGINE_RESOURCE_H
#define FIRSTENGINE_RESOURCE_H

#include <memory>
#include <string>
namespace firstengine
{
	struct Core;
	struct CacheManager;
	/********************************************//**
	* \brief Resource gives a way to load in data 
	***********************************************/
	struct Resource
	{
		friend struct firstengine::CacheManager;
		/********************************************//**
		* \brief Calls onLoad
		***********************************************/
		void load();
		/********************************************//**
		* \brief Designed to be overridden with specific Resource loading instructions
		***********************************************/
		virtual void onLoad() {};
		/********************************************//**
		* \brief Returns a reference to Core
		***********************************************/
		std::weak_ptr<Core> getCore();

	protected:
		std::string path;
		std::weak_ptr<CacheManager> cache;
	};
}


#endif

