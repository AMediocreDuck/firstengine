#ifndef FIRSTENGINE_KEYBOARD_H
#define FIRSTENGINE_KEYBOARD_H

#include <vector>
#include <SDL2/SDL.h>
namespace firstengine
{
	struct Core;
	/********************************************//**
	* \brief Keyboard Inputs and store
	***********************************************/
	struct Keyboard
	{
		/********************************************//**
		* \brief Checks to see whether a specified key has been pressed that frame
		***********************************************/
		bool getKey(int key);
		/********************************************//**
		* \brief Checks if a specified key is down that frame
		***********************************************/
		bool getKeyDown(int key);
		/********************************************//**
		* \brief Checks if specified key has been lifted this frame
		***********************************************/
		bool getKeyUp(int key);

	private:
		friend struct firstengine::Core;
		void addKey(SDL_Keycode _key);
		void removeKey(SDL_Keycode _key);
		void clearUpDown();

		std::vector<int> keys;
		std::vector<int> downKeys;
		std::vector<int> upKeys;
	};
}



#endif 
