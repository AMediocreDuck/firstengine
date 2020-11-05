#ifndef FIRSTENGINE_vShader_H
#define FIRSTENGINE_vShader_H

#include "Resource.h"
#include "GL/glew.h"

namespace firstengine
{
	struct vShader : public Resource
	{
		void onLoad();
	private:
		friend struct Renderer;
		GLuint shaderId;
	};

}



#endif
