#ifndef FIRSTENGINE_CORE_H
#define FIRSTENGINE_CORE_H

#include <memory> 
#include <vector>
#include <rend/rend.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <firstengine/Exception.h>

namespace firstengine
{

	struct Entity;
	struct Core
	{
		static std::shared_ptr<Core> initialize();
		std::shared_ptr<Entity> addEntity();
		void start();
	private:
		std::vector<std::shared_ptr<Entity>> entities;
		std::weak_ptr<Core> self;
		SDL_Window* window;
		SDL_GLContext glContext;
		std::shared_ptr<rend::Context> context;
	};
}
#endif