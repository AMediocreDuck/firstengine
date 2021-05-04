#ifndef FIRSTENGINE_THREADMANAGER_H
#define FIRSTENGINE_THREADMANAGER_H


#include <thread>
#include <mutex>
#include <iostream>
#include <vector>
#include <functional>
#include <memory>

#include "firstengine/Component.h"

namespace firstengine
{
	struct Mutex
	{
	public:
		Mutex(int _id) { Id = _id; }
		int Id;
		std::mutex mutex;
	};
	struct ThreadManager : Component
	{
		template<typename T, typename... Args>
		T createThread(std::function<T()> Task, Args&&... args)
		{
			std::shared_ptr<std::thread> tmpThread = std::make_shared<std::thread>(Task, std::forward<Args>(args)...);

			try
			{
				threads.push_back(tmpThread);
			}
			catch (std::exception& e0)
			{
				std::cout << "Thread Already Ended" << std::endl;
			}

		}
		template<typename T, typename a, typename... Args>
		T createThread(std::function<T(a)> Task, Args&&... args)
		{
			std::shared_ptr<std::thread> tmpThread = std::make_shared<std::thread>(Task, std::forward<Args>(args)...);

			try
			{
				threads.push_back(tmpThread);
			}
			catch (std::exception& e1)
			{
				std::cout << "Thread Already Ended" << std::endl;
			}

		}
		template<typename T, typename a, typename b, typename... Args>
		T createThread(std::function<T(a, b)> Task, Args&&... args)
		{
			std::shared_ptr<std::thread> tmpThread = std::make_shared<std::thread>(Task, std::forward<Args>(args)...);

			try
			{
				threads.push_back(tmpThread);
			}
			catch (std::exception& e2)
			{
				std::cout << "Thread Already Ended" << std::endl;
			}
			catch (...)
			{
				std::cout << "Thread Already Ended" << std::endl;
			}

		}
		template<typename T, typename a, typename b, typename c, typename... Args>
		T createThread(std::function<T(a, b, c)> Task, Args&&... args)
		{
			std::shared_ptr<std::thread> tmpThread = std::make_shared<std::thread>(Task, std::forward<Args>(args)...);

			try
			{
				threads.push_back(tmpThread);
			}
			catch (std::exception& e3)
			{
				std::cout << "Thread Already Ended" << std::endl;
			}

		}
		template<typename T, typename a, typename b, typename c, typename d, typename... Args>
		T createThread(std::function<T(a, b, c, d)> Task, Args&&... args)
		{
			std::shared_ptr<std::thread> tmpThread = std::make_shared<std::thread>(Task, std::forward<Args>(args)...);

			try
			{
				threads.push_back(tmpThread);
			}
			catch (std::exception& e4)
			{
				std::cout << "Thread Already Ended" << std::endl;
			}

		}
		template<typename T, typename a, typename b, typename c, typename d, typename e, typename... Args>
		T createThread(std::function<T(a, b, c, d, e)> Task, Args&&... args)
		{
			std::shared_ptr<std::thread> tmpThread = std::make_shared<std::thread>(Task, std::forward<Args>(args)...);

			try
			{
				threads.push_back(tmpThread);
			}
			catch (std::exception& e5)
			{
				std::cout << "Thread Already Ended" << std::endl;
			}

		}
		void onInitialize();

		void shutDownThreads();
		void removeInactive();

		std::shared_ptr<Mutex> createMutex(int _Id);
		std::shared_ptr<Mutex> getMutex(int _Id);


	private:
		std::vector<std::shared_ptr<std::thread>> threads;
		std::vector<std::shared_ptr<Mutex>> mutexes;
		//std::vector<std::function<void(Args&&...args)>> funcQueue;
	};
}
#endif