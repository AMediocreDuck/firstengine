#ifndef FIRSTENGINE_TEXTURE_H
#define FIRSTENGINE_TEXTURE_H

#include "Resource.h"

#include <memory>
#include <GL/glew.h> // GLuint
#include "fegraphics/Texture.h"

namespace firstengine
{
	struct Renderer;
	/********************************************//**
	* \brief Stores the data for a texture
	***********************************************/
	struct Texture : public Resource
	{
		/********************************************//**
		* \brief Used to load in textures
		***********************************************/
		void onLoad();


	private:
		friend struct firstengine::Renderer;
		std::shared_ptr<fegraphics::Texture> fegTexture;
	};
}
#endif
