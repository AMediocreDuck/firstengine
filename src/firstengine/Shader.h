#ifndef FIRSTENGINE_SHADER_H
#define FIRSTENGINE_SHADER_H

#include "Resource.h"
#include "fegraphics/ShaderProgram.h"

namespace firstengine
{
	struct vShader;
	struct fShader;
	struct Renderer;
	/********************************************//**
	*  \brief Wrapper Class for the ShaderProgram Resource
	***********************************************/
	struct Shader : public Resource
	{
		~Shader();
		/********************************************//**
		*  \brief Loads the appropriate data for the Resource to be used
		***********************************************/
		void onLoad();
	private:
		friend struct firstengine::Renderer;
		std::shared_ptr<vShader> vertShader;
		std::shared_ptr<fShader> fragShader;
		std::shared_ptr<fegraphics::ShaderProgram> fegShaderProgram;
	};
}
#endif
