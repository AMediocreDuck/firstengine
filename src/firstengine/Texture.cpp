#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb-master/stb_image.h>
#include "firstengine/Exception.h"

namespace firstengine
{

	void Texture::onLoad()
	{
		data = stbi_load(path.c_str(), &w, &h, NULL, 4);
	}


}