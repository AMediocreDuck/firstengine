#ifndef FIRSTENGINE_FShader_H
#define FIRSTENGINE_FShader_H

#include "Resource.h"
#include <GL/glew.h>
#include <string>

namespace firstengine
{
	struct Shader;
	/********************************************//**
	* \brief Wrapper Class for Fragment Shader
	***********************************************/
	struct fShader : public Resource
	{
		void onLoad();
	private:
		friend struct firstengine::Shader;
		std::string data;
		//GLuint shaderId;
	};

}
#endif

