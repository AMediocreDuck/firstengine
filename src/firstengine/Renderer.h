#ifndef FIRSTENGINE_RENDERER_H
#define FIRSTENGINE_RENDERER_H

#include "Component.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "fegraphics/fegraphics.h"
#include <memory>



namespace firstengine
{
	struct Shader;
	struct Model;
	struct Texture;
	struct vShader;
	struct fShader;
	/********************************************//**
	* \brief Component for rendering to the screen
	***********************************************/
	struct Renderer : public Component
	{
		/********************************************//**
		* \brief Ran when the Renderer is first created 
		***********************************************/
		void onInitialize();
		/********************************************//**
		* \brief Holds all of the Rendering functionality
		***********************************************/
		void onRender();
		/********************************************//**
		* \brief Sets the Vertex Shader the Renderer will use
		***********************************************/
		void setvShader(const char* path);
		/********************************************//**
		* \brief Sets the Fragment Shader the Renderer will use
		***********************************************/
		void setfShader(const char* path);
		/********************************************//**
		* \brief Returns the deltaTime
		***********************************************/
		//void setTexture(const char* path);
		/********************************************//**
		* \brief Adds a Texture to the Renderer that will be used when Rendering
		***********************************************/
		void addTexture(const char* path);
		/********************************************//**
		* \brief Sets which Model should be Rendered
		***********************************************/
		void setModel(const char* path);
		/********************************************//**
		* \brief Used to set both the Fragment and Vertex Shader
		***********************************************/
		void setShader(const char* path);
;

	private:
		glm::mat4 getProjectionMat();
		glm::mat4 getModelMat();

		std::shared_ptr<Shader> shaderProgram;
		//std::shared_ptr<fegraphics::ShaderProgram> shaderProgram;
		bool dirty = true;;
		std::shared_ptr<vShader> vertexShader;
		std::shared_ptr<fShader> fragmentShader;
		std::shared_ptr<firstengine::Model> model;
		std::vector<std::shared_ptr<Texture>> Textures;

	};
}
#endif
