
#include "Sound.h"
#include "firstengine/Exception.h"

#include <stb-master/stb_vorbis.c>


namespace firstengine
{
	void Sound::onLoad()
	{

		alGenBuffers(1, &soundId);
		ALenum format = 0;
		ALsizei freq = 0;
		std::vector<char> bufferData;

		loadOgg(path + ".ogg", bufferData, format, freq);

		alBufferData(soundId, format, &bufferData.at(0),
			static_cast<ALsizei>(bufferData.size()), freq);

	}

	void Sound::loadOgg(const std::string& fileName,
		std::vector<char>& buffer, ALenum& format, ALsizei& freq)
	{
		int channels = 0;
		int sampleRate = 0;
		short* output = NULL;
		size_t samples = stb_vorbis_decode_filename(
			fileName.c_str(), &channels, &sampleRate, &output);
		if (samples == -1)
		{
			throw firstengine::Exception("Failed to open file '" + fileName + "'");
		}
		// Record the format required by OpenAL
		if (channels == 1)
		{
			format = AL_FORMAT_MONO16;
		}
		else
		{
			format = AL_FORMAT_STEREO16;
		}
		// Record the sample rate required by OpenAL
		freq = sampleRate;
		buffer.resize(samples * 2);
		memcpy(&buffer.at(0), output, buffer.size());
		// Clean up the read data
		free(output);
	}
}