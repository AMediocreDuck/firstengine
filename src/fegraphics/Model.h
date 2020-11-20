#ifndef FEGRAPHICS_MODEL_H
#define FEGRAPHICS_MODEL_H

#include <memory>
#include <GL/glew.h>

namespace fegraphics 
{
	struct Context;
	struct Model
	{
		~Model();
		void setModel(GLuint _vaoId, size_t _numVerts);
		GLuint getVao() { return vaoId; };
		size_t getNumVerts() { return numVerts; };
	private:
		friend struct fegraphics::Context;
		std::shared_ptr<Context> context;
		GLuint vaoId;
		size_t numVerts;
	};
}


#endif
