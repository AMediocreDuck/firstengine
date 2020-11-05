#ifndef FIRSTENGINE_MODEL_H
#define FIRSTENGINE_MODEL_H

#include "Resource.h"
#include <memory>
#include <GL/glew.h>

namespace firstengine 
{
	struct Texture;
	struct Model : public Resource
	{
		Model::Model() { vaoId = NULL; numVerts = NULL;};
		void onLoad();
	private:
		friend struct Renderer;
		GLuint vaoId;
		size_t numVerts;
	};
}


#endif
