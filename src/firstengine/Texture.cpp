#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb-master/stb_image.h>
#include "firstengine/Exception.h"

#include "Core.h"
#include "CacheManager.h"

namespace firstengine
{

	void Texture::onLoad()
	{
		int w;
		int h;
		unsigned char* data;
		data = stbi_load(path.c_str(), &w, &h, NULL, 4);
		fegTexture = cache.lock()->getCore()->context->createTexture();
		fegTexture->setTextureData(data, w, h);
	}


}