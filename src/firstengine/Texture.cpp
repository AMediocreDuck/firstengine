#include "Texture.h"


#define STB_IMAGE_IMPLEMENTATION
#include <stb-master/stb_image.h>
#include "firstengine//Exception.h"

namespace firstengine
{
	Texture::Texture()
	{
	}

	void Texture::onLoad()
	{
		unsigned char* data = stbi_load(path.c_str(), &imgWidth, &imgHeight, NULL, 4);

		if (!data)
		{
			throw firstengine::Exception("Failed to load Texture");
		}
		glGenTextures(1, &textureId);

		if (!textureId)
		{
			throw firstengine::Exception("Failed to set texture Id");
		}

		glBindTexture(GL_TEXTURE_2D, textureId);

		// Upload the image data to the bound texture unit in the GPU
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, data);

		// Free the loaded data because we now have a copy on the GPU
		free(data);

		// Generate Mipmap so the texture can be mapped correctly
		glGenerateMipmap(GL_TEXTURE_2D);

		// Unbind the texture because we are done operating on it
		glBindTexture(GL_TEXTURE_2D, 0);
	}


	Texture::~Texture()
	{
		glDeleteTextures(1, &textureId);
	}
}