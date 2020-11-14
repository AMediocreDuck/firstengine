#include "Keyboard.h"

namespace firstengine
{

	bool Keyboard::getKey(int key)
	{
		for (size_t ki = 0; ki < keys.size(); ki++)
		{
			if (keys.at(ki) == key)
			{
				return true;
			}
		}
		return false;
	}

	bool Keyboard::getKeyDown(int key)
	{
		for (size_t ki = 0; ki < downKeys.size(); ki++)
		{
			if (downKeys.at(ki) == key)
			{
				return true;
			}
		}
		return false;
	}

	bool Keyboard::getKeyUp(int key)
	{
		for (size_t ki = 0; ki < upKeys.size(); ki++)
		{
			if (upKeys.at(ki) == key)
			{
				return true;
			}
		}
		return false;
	}
	void Keyboard::addKey(SDL_Keycode _key)
	{
		keys.push_back(_key);
		downKeys.push_back(_key);
	}
	void Keyboard::removeKey(SDL_Keycode _key)
	{
		upKeys.push_back(_key);
		for (std::vector<int>::iterator it = keys.begin(); it != keys.end();)
		{
			if (*it == _key)
			{
				it = keys.erase(it);
			}
			else it++;
		}
	}

	void Keyboard::clearUpDown()
	{
		downKeys.clear();
		upKeys.clear();
	}
}