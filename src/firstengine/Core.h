#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

#ifndef FIRSTENGINE_CORE_H
#define FIRSTENGINE_CORE_H


#include <memory> 
#include <vector>
#include <fegraphics/fegraphics.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <AL/al.h>
#include <AL/alc.h>


namespace firstengine
{
	struct Context;
	struct CacheManager;
	struct Entity;
	struct Screen;
	struct Keyboard;
	struct Core
	{
		~Core();
		static std::shared_ptr<Core> initialize();
		std::shared_ptr<Entity> addEntity();
		void start();
		std::shared_ptr<Screen> getScreen();
		std::shared_ptr<Keyboard> getKeyboard();
		


		//SDL_Window* window;
		//SDL_GLContext glContext;
		bool soundWorking;
		ALCdevice* alDevice;
		ALCcontext* alContext;

		std::shared_ptr<fegraphics::Context> context;

		std::shared_ptr<CacheManager> cacheManager;
	private:
#ifdef EMSCRIPTEN
		static bool Loop();
#else 
		bool Loop();
#endif
		SDL_Window* window;
		SDL_GLContext glContext;
		std::vector<std::shared_ptr<Entity>> entities;
		std::shared_ptr<Screen> screen;
		std::shared_ptr<Keyboard> keyboard;
		std::weak_ptr<Core> self;

	};
}
#endif