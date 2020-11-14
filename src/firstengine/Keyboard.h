#ifndef FIRSTENGINE_KEYBOARD_H
#define FIRSTENGINE_KEYBOARD_H

#include <vector>
#include <SDL2/SDL.h>
namespace firstengine
{
	struct Core;
	struct Keyboard
	{
		bool getKey(int key);
		bool getKeyDown(int key);
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
