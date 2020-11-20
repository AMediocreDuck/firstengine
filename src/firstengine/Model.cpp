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
		fegModel->setModel(buLoadModel(path, &numVerts), numVerts);
	}
}