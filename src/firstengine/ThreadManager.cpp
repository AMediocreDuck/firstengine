#include "firstengine/ThreadManager.h"
#include "firstengine//Core.h"
#include "firstengine/Entity.h"

namespace firstengine
{
	void ThreadManager::onInitialize()
	{
		if (getCore()->networkManager == nullptr)
		{
			std::shared_ptr<ThreadManager> self = getEntity()->getComponent<ThreadManager>();
			getCore()->threadManager = self;

		}
		else
		{
			throw firstengine::Exception("Thread Manager Already Exists");
		}
	}
	void ThreadManager::shutDownThreads()
	{
		std::vector<std::shared_ptr<std::thread>>::iterator it = threads.begin();
		for (it; it != threads.end(); it++)
		{
			if (it->get()->joinable())
			{
				it->get()->join();
			}
		}
	}

	std::shared_ptr<Mutex> ThreadManager::createMutex(int _Id)
	{
		for (std::vector<std::shared_ptr<Mutex>>::iterator it = mutexes.begin(); it != mutexes.end(); ++it)
		{
			if (it->get()->Id == _Id)
			{
				throw firstengine::Exception("Mutex ID already in Use");
			}
		}
		std::shared_ptr<Mutex> tmpMutex = std::make_shared<Mutex>(_Id);
		mutexes.push_back(tmpMutex);
		return tmpMutex;
	}

	std::shared_ptr<Mutex> ThreadManager::getMutex(int _Id)
	{
		for (std::vector<std::shared_ptr<Mutex>>::iterator it = mutexes.begin(); it != mutexes.end(); ++it)
		{
			if(it->get()->Id == _Id)
			{
				return *it;
			}
		}
		throw firstengine::Exception("Mutex Not Found");
	}

	void ThreadManager::removeInactive()
	{
		std::vector<std::shared_ptr<std::thread>>::iterator it = threads.begin();
		for (it; it != threads.end(); it++)
		{
			if (!it->get()->joinable())
			{
				it->get()->join();
			}

		}
	}
}