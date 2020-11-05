#include "Core.h"
#include "CacheManager.h"
#include "Entity.h"
#include <iostream>
#include "Screen.h"
#include "Transform.h"
#include "firstengine/Exception.h"
#include "Context.h"

namespace firstengine
{
	struct Transform;
#ifdef EMSCRIPTEN
	std::weak_ptr<Core> _core;
#endif
	std::shared_ptr<Core> Core::initialize()
	{

		std::shared_ptr<Core> rtn = std::make_shared<Core>();
		rtn->self = rtn;

		int w;
		int h;
		rtn->window = SDL_CreateWindow("firstengine",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			800, 600,
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		rtn->screen = std::make_shared<Screen>();
		rtn->screen->setWindowSize(rtn->window);

		if (!rtn->window)
		{
			throw firstengine::Exception("Failed to create window");
		}
		rtn->glContext = SDL_GL_CreateContext(rtn->window);
		if (!rtn->glContext)
		{
			throw firstengine::Exception("Failed to create OpenGL context");
		}
		rtn->context = Context::initialize();
		rtn->cacheManager = std::make_shared<CacheManager>();
		rtn->cacheManager->core = rtn->self;
		rtn->cacheManager->self = rtn->cacheManager;
#ifdef EMSCRIPTEN
		_core = rtn;
#endif
		return rtn;
	}
	std::shared_ptr<Entity> Core::addEntity()
	{
		std::shared_ptr <Entity> rtn = std::make_shared <Entity>();
		rtn->core = self;
		rtn->self = rtn;
		entities.push_back(rtn);
		rtn->addComponent<Transform>();
		return rtn;
	}
#ifdef EMSCRIPTEN
		void Core::start()
		{
			emscripten_set_main_loop(Core::loop, 0, 1);
		}

		void Core::loop()
		{
			//bool running = true;
			SDL_Event e = { 0 };
			//while (running)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						//running = false;
					}
				}
				for (size_t ei = 0; ei < _core.lock()->entities.size(); ei++)
				{
					_core.lock()->entities.at(ei)->tick();
				}
				glClearColor(0.39f, 0.8f, 0.93f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				for (size_t ei = 0; ei < _core.lock()->entities.size(); ei++)
				{
					_core.lock()->entities.at(ei)->render();
				}
				SDL_GL_SwapWindow(_core.lock()->window);
				std::cout << "End" << std::endl;
			}
		}
#else
	void Core::start()
	{
		bool running = true;
		SDL_Event e = { 0 };
		while (running)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					running = false;
				}
			}
			for (size_t ei = 0; ei < entities.size(); ei++)
			{
				entities.at(ei)->tick();
			}
			glClearColor(0.39f, 0.8f, 0.93f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			for (size_t ei = 0; ei < entities.size(); ei++)
			{
				entities.at(ei)->render();
			}
			SDL_GL_SwapWindow(window);
		}
	}
#endif

	std::weak_ptr<Screen> Core::getScreen()
	{
		std::weak_ptr<Screen> rtn = screen;
		return rtn;
	}
}
/*
void Core::start()
{
	bool running = true;
	SDL_Event e = { 0 };
	while (running)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				running = false;
			}
		}
		for (size_t ei = 0; ei < entities.size(); ei++)
		{
			entities.at(ei)->tick();
		}
		glClearColor(0.39f, 0.8f, 0.93f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (size_t ei = 0; ei < entities.size(); ei++)
		{
			entities.at(ei)->render();
		}
		SDL_GL_SwapWindow(window);
	}
}
*/