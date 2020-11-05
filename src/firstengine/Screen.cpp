#include "Screen.h"

#include <glm/ext.hpp>

namespace firstengine
{
	glm::mat4 Screen::getPerspective(float _angle, float _nearPlane, float _farPlane)
	{
		glm::mat4 projection = glm::perspective(glm::radians(_angle),
			float(width / height), _nearPlane, _farPlane);
		return projection;
	}
	void Screen::setWindowSize(SDL_Window *window)
	{
		 SDL_GetWindowSize(window, &width, &height);
	}
}