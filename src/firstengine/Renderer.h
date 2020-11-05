#ifndef FIRSTENGINE_RENDERER_H
#define FIRSTENGINE_RENDERER_H

#include "Component.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
//#include <rend/rend.h>
#include <memory>

namespace firstengine
{
	struct ShaderProgram;
	struct vShader;
	struct fShader;
	struct Model;
	struct Texture;
	struct Renderer : public Component
	{
		void onInitialize();
		void onRender();

		void setvShader(const char* path);
		void setfShader(const char* path);
		void setTexture(const char* path);
		void setModel(const char* path);
;

	private:
		std::shared_ptr<ShaderProgram> createShaderProgam();

		glm::mat4 getProjectionMat();
		glm::mat4 getModelMat();
		std::shared_ptr<Model> getModel();

		std::shared_ptr<ShaderProgram> shaderProgram;
		bool dirty;
		std::shared_ptr<vShader> vertexShader;
		std::shared_ptr<fShader> fragmentShader;
		std::shared_ptr<Model> model;
		std::shared_ptr<Texture> texture;

	};
}
#endif
