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
		/********************************************//**
		* \brief Function called when Shader has been loaded 
		***********************************************/
		void onLoad();
	private:
		friend struct firstengine::Shader;
		std::string data;
		//GLuint shaderId;
	};

}
#endif

