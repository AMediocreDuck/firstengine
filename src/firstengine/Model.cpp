#include "Model.h"
#include "Texture.h"
#include "bugl.h"

namespace firstengine
{
	void Model::onLoad()
	{
		vaoId = buLoadModel(path, &numVerts);
	}
}
