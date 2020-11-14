#include "Core.h"
#include "CacheManager.h"
#include "Entity.h"
#include <iostream>
#include "Screen.h"
#include "Keyboard.h"
#include "Transform.h"
#include "firstengine/Exception.h"
#include "feGraphics/Context.h"

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
		rtn->soundWorking = true;

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
		rtn->alDevice = alcOpenDevice(NULL);
		if (!rtn->alDevice)
		{
			rtn->soundWorking = false;
			//throw firstengine::Exception("Failed to open default device");
		}
		if (rtn->soundWorking)
		{
			rtn->alContext = alcCreateContext(rtn->alDevice, NULL);
			if (!rtn->alContext)
			{
				alcCloseDevice(rtn->alDevice);
				rtn->soundWorking = false;
				//throw firstengine::Exception("Failed to create AL context");
			}
			if (!alcMakeContextCurrent(rtn->alContext))
			{
				alcDestroyContext(rtn->alContext);
				alcCloseDevice(rtn->alDevice);
				rtn->soundWorking = false;
				//throw Exception("Failed to make context current");
			}
		}
		rtn->context = fegraphics::Context::initialize();
		rtn->cacheManager = std::make_shared<CacheManager>();
		rtn->keyboard = std::make_shared<Keyboard>();
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
		rtn->addComponent<Transform>();
		entities.push_back(rtn);
		return rtn;
	}
		void Core::start()
		{
#ifdef EMSCRIPTEN
			emscripten_set_main_loop(Core::Loop, 0, 1);
#else
			bool running = true;
			while (running)
			{
				running = Loop();
			}
#endif
		}

		bool Core::Loop()
		{
			SDL_Event e = { 0 };
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					return false;
				}
				else if (e.type == SDL_KEYDOWN)
				{
					keyboard->addKey(e.key.keysym.sym);
				}
				else if (e.type == SDL_KEYUP)
				{
					keyboard->removeKey(e.key.keysym.sym);
				}
			}

			for (size_t ei = 0; ei < entities.size(); ei++)
			{
				entities.at(ei)->tick();
			}
			screen->setWindowSize(window);
			glClearColor(0.39f, 0.8f, 0.93f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			for (size_t ei = 0; ei < entities.size(); ei++)
			{
				entities.at(ei)->render();
			}
			SDL_GL_SwapWindow(window);
			keyboard->clearUpDown();
			return true;
		}

	std::shared_ptr<Screen> Core::getScreen()
	{
		std::weak_ptr<Screen> rtn = screen;
		return rtn.lock();
	}

	std::shared_ptr<Keyboard> Core::getKeyboard()
	{
		std::weak_ptr<Keyboard> rtn = keyboard;
		return rtn.lock();
	}

	 Core::~Core()
	{
		alcMakeContextCurrent(NULL);
		alcDestroyContext(alContext);
		alcCloseDevice(alDevice);
		SDL_DestroyWindow(window);
		SDL_Quit();
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