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

	struct Renderer : public Component
	{
		void onInitialize();
		void onRender();

		void setvShader(const char* path);
		void setfShader(const char* path);
		void setTexture(const char* path);
		void addTexture(const char* path);
		void setModel(const char* path);
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
