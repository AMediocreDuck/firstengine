#include "Model.h"
#include "feGraphics/bugl.h"
#include "firstengine/CacheManager.h"
#include "firstengine/Core.h"

namespace firstengine
{

	void Model::onLoad()
	{
		fegModel = cache.lock()->getCore()->context->createModel();

		size_t numVerts = 0;
		GLuint vaoID = buLoadModel(path, &numVerts);
		std::cout << "Model About to be Loaded" << std::endl;
		fegModel->setModel( vaoID, numVerts);
	}
}