#include "Model.h"
#include "Texture.h"
#include "bugl.h"

namespace fegraphics
{
	void Model::setModel(GLuint _vaoId, size_t _numVerts)
	{
		vaoId = _vaoId;
		numVerts = _numVerts;
	}
}
