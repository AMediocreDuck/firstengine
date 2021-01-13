#ifndef FIRSTENGINE_VShader_H
#define FIRSTENGINE_VShader_H

#include "Resource.h"
#include <GL/glew.h>
#include <string>

namespace firstengine
{
	struct Shader;
	/********************************************//**
	* \brief Stores teh Vertex shader data
	***********************************************/
	struct vShader : public Resource
	{
		/********************************************//**
		* \brief Used to load the required data
		***********************************************/
		void onLoad();
	private:
		friend struct firstengine::Shader;
		std::string data;
		//GLuint shaderId;
	};

}
#endif
