#ifndef FIRSTENGINE_TEXTURE_H
#define FIRSTENGINE_TEXTURE_H

#include "Resource.h"

#include <memory>
#include <GL/glew.h> // GLuint

namespace firstengine
{
	struct Texture : public Resource
	{
		Texture();
		void Texture::onLoad();
		~Texture();
		GLuint getTextureId() { return textureId; }

	private:
		friend struct Context;
		std::shared_ptr<Context> context;
		int imgWidth;
		int imgHeight;
		GLuint textureId;
	};
}
#endif
