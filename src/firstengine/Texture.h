#ifndef FIRSTENGINE_TEXTURE_H
#define FIRSTENGINE_TEXTURE_H

#include "Resource.h"

#include <memory>
#include <GL/glew.h> // GLuint
#include "fegraphics/Texture.h"

namespace firstengine
{
	struct Renderer;
	struct Texture : public Resource
	{
		void onLoad();


	private:
		friend struct firstengine::Renderer;
		std::shared_ptr<fegraphics::Texture> fegTexture;
	};
}
#endif
