#include "SoundSource.h"
#include "Sound.h"
#include "Core.h"
#include "CacheManager.h"
#include "Entity.h"

namespace firstengine
{
	void SoundSource::onInitialize()
	{
		soundWorking = getCore()->soundWorking;
		if (soundWorking)
		{
			alGenSources(1, &ssId);
		}
		//alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
		//alSource3f(sid, AL_POSITION, 0.0f, 0.0f, 0.0f);
		//alSourcei(ssId, AL_BUFFER, sound->soundId);
		//alSourcePlay(ssId);

	}

	void SoundSource::onTick()
	{
		if (soundWorking)
		{
			ALint state = 0;
			alGetSourcei(ssId, AL_SOURCE_STATE, &state);
			if (state == AL_STOPPED)
			{
				destroy();
			}
		}
	}

	void SoundSource::setSound(const char* path)
	{
		if (soundWorking)
		{
			sound = getCore()->cacheManager->loadResource<Sound>(path);
			alSourcei(ssId, AL_BUFFER, sound->soundId);
			alSourcePlay(ssId);
		}
	}
	void SoundSource::onDestroy()
	{
		if (soundWorking)
		{
			alDeleteSources(1, &ssId);
		}
	}

}