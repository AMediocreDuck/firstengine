#include "Texture.h"

//#define STB_IMAGE_IMPLEMENTATION
//#include <stb-master/stb_image.h>

namespace fegraphics
{
	Texture::Texture()
	{

	}
	GLuint Texture::getId()
	{
		if (dirty)
		{
			glBindTexture(GL_TEXTURE_2D, textureId);

			// Upload the image data to the bound texture unit in the GPU
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA,
				GL_UNSIGNED_BYTE, data);

			// Free the loaded data because we now have a copy on the GPU
			free(data);

			// Generate Mipmap so the texture can be mapped correctly
			glGenerateMipmap(GL_TEXTURE_2D);

			// Unbind the texture because we are done operating on it
			glBindTexture(GL_TEXTURE_2D, 0);
			dirty = false;
		}
		return textureId;
	}
	void Texture::setTextureData(unsigned char* _data, int _w, int _h)
	{
		data = _data;
		texHeight = _h;
		texWidth = _w;
		dirty = true;
	}


	Texture::~Texture()
	{
		glDeleteTextures(1, &textureId);
	}
}