#ifndef FIRSTENGINE_VShader_H
#define FIRSTENGINE_VShader_H

#include "Resource.h"
#include <GL/glew.h>
#include <string>

namespace firstengine
{
	struct Renderer;
	struct vShader : public Resource
	{
		void onLoad();
	private:
		friend struct firstengine::Renderer;
		std::string data;
		//GLuint shaderId;
	};

}
#endif
