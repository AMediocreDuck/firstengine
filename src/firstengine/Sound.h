#ifndef FIRSTENGINE_SOUND_H
#define FIRSTENGINE_SOUND_H

#include "Resource.h"

#include <vector>
#include <memory>
#include <GL/glew.h> // GLuint
#include <AL/al.h> 


namespace firstengine
{
	struct SoundSource;
	struct Sound : public Resource
	{
		void onLoad();
	private:
		friend struct firstengine::SoundSource;
		void loadOgg(const std::string& fileName,
			std::vector<char>& buffer, ALenum& format, ALsizei& freq);
		ALuint soundId;
	};
}
#endif
