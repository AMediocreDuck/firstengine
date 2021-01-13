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
	/********************************************//**
	* \brief Resource for Sounds
	***********************************************/
	struct Sound : public Resource
	{
		/********************************************//**
		* \brief Used to load all the required data
		***********************************************/
		void onLoad();
	private:
		friend struct firstengine::SoundSource;
		void loadOgg(const std::string& fileName,
			std::vector<char>& buffer, ALenum& format, ALsizei& freq);
		ALuint soundId;
	};
}
#endif
