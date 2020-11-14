#ifndef FIRSTENGINE_TEXTURE_H
#define FIRSTENGINE_TEXTURE_H

#include "Resource.h"

#include <memory>
#include <GL/glew.h> // GLuint

namespace firstengine
{
	struct Renderer;
	struct Texture : public Resource
	{
		void onLoad();


	private:
		friend struct firstengine::Renderer;
		unsigned char* data;
		int w;
		int h;
		//GLuint textureId;
	};
}
#endif
