#ifndef FIRSTENGINE_SOUNDSOURCE_H
#define FIRSTENGINE_SOUNDSOURCE_H


#include "Component.h"
#include <memory>
#include <AL/al.h>

namespace firstengine
{
	struct Sound;
	struct SoundSource : public Component
	{
		void onInitialize();
		void onTick();
		void onDestroy();
		void setSound(const char* path);
	private:
		bool soundWorking;
		std::shared_ptr<Sound> sound;
		ALuint ssId;

	};
}


#endif