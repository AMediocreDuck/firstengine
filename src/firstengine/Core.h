#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

#ifndef FIRSTENGINE_CORE_H
#define FIRSTENGINE_CORE_H


#include <memory> 
#include <vector>
#include <rend/rend.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>



namespace firstengine
{
	struct Context;
	struct CacheManager;
	struct Entity;
	struct Screen;
	struct Core
	{
		static std::shared_ptr<Core> initialize();
		std::shared_ptr<Entity> addEntity();
		void start();


		SDL_Window* window;
		SDL_GLContext glContext;
		std::shared_ptr<firstengine::Context> context;
		std::weak_ptr<Screen> getScreen();
		std::shared_ptr<CacheManager> cacheManager;
	private:
#ifdef EMSCRIPTEN
		static void loop();
#endif

		std::vector<std::shared_ptr<Entity>> entities;
		std::shared_ptr<Screen> screen;
		std::weak_ptr<Core> self;

	};
}
#endif