#ifndef FIRSTENGINE_MODEL_H
#define FIRSTENGINE_MODEL_H

#include <memory>
#include <GL/glew.h>
#include "Resource.h"

namespace firstengine
{
	struct Context;
	struct Renderer;
	struct Model : public Resource
	{
		~Model();
		void onLoad();
		//GLuint getVaoId() { return vaoId; }
		//size_t getNumVerts() { return numVerts; }
	private:
		friend struct firstengine::Renderer;
		GLuint vaoId;
		size_t numVerts;
	};
}


#endif
