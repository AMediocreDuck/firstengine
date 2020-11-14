#include "Model.h"
#include "feGraphics/bugl.h"

namespace firstengine
{
	Model::~Model()
	{
		glDeleteVertexArrays(1, &vaoId);
	}

	void Model::onLoad()
	{
		vaoId = buLoadModel(path, &numVerts);
	}
}