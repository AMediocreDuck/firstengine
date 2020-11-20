#include "Model.h"
#include "Texture.h"
#include "bugl.h"

namespace fegraphics
{
	Model::~Model()
	{
		GLuint destVao = vaoId;
		glDeleteVertexArrays(1, &destVao);
	}

	void Model::setModel(GLuint _vaoId, size_t _numVerts)
	{
		vaoId = _vaoId;
		numVerts = _numVerts;
	}
}
