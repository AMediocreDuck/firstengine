#ifndef FIRSTENGINE_SCREEN_H
#define FIRSTENGINE_SCREEN_H

#include <glm/glm.hpp>
#include <SDL2/SDL.h>

namespace firstengine
{
	/********************************************//**
	* \brief Holds data about the display
	***********************************************/
	struct Screen
	{
		/********************************************//**
		* \brief Returns the perception matrix 
		***********************************************/
		glm::mat4 getPerspective(float _angle, float _nearPlane, float _farPlane);
		/********************************************//**
		* \brief Returns the Screen width
		***********************************************/
		int getWidth() { return width; }
		/********************************************//**
		* \brief Returns the Screen height
		***********************************************/
		int getHeight() { return height; }
		/********************************************//**
		* \brief Sets a reference to the SDL window 
		***********************************************/
		void setWindowSize(SDL_Window* window);
	private:
		int width;
		int height;

	};
}
#endif 
