#ifndef FIRSTENGINE_fShader_H
#define FIRSTENGINE_fShader_H

#include "Resource.h"
#include "GL/glew.h"

namespace firstengine
{
	struct fShader : public Resource
	{
		void onLoad();
	private:
		friend struct Renderer;
		GLuint shaderId;
	};

}
#endif
