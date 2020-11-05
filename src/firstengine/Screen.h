#ifndef FIRSTENGINE_SCREEN_H
#define FIRSTENGINE_SCREEN_H

#include <glm/glm.hpp>
#include <SDL2/SDL.h>

namespace firstengine
{
	struct Screen
	{
		glm::mat4 getPerspective(float _angle, float _nearPlane, float _farPlane);
		void setWindowSize(SDL_Window* window);
	private:
		int width;
		int height;

	};
}
#endif 
