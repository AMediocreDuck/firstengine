#include "Renderer.h"

#include <string>
#include <glm/glm.hpp>
#include "Entity.h"
#include "Core.h"
#include "CacheManager.h"
#include "Context.h"
#include "firstengine/Exception.h"
#include "Screen.h"
#include "Transform.h"

#include "ShaderProgram.h"
#include "Model.h"
#include "Texture.h"
#include "bugl.h"

#include "vShader.h"
#include "fShader.h"




namespace firstengine
{
	void Renderer::onInitialize()
	{
		shaderProgram = createShaderProgam();
	}
	void Renderer::onRender()
	{
		if (dirty)
		{
		shaderProgram->setShaders();
		dirty = false;
		}

		glUseProgram(shaderProgram->getProgramId());
		shaderProgram->uploadProjectionMatrix(getProjectionMat());
		shaderProgram->uploadModelMatrix(getModelMat());
		shaderProgram->render(model->vaoId, model->numVerts, true, true, true,texture);
	}
	std::shared_ptr<ShaderProgram> Renderer::createShaderProgam()
	{
		return getCore()->context->createShader();
	}

	void Renderer::setvShader(const char* path)
	{
		vertexShader = getCore()->cacheManager->loadResource<vShader>(path);
		shaderProgram->setvShaderId(vertexShader->shaderId);
		dirty = true;
	}
	void Renderer::setfShader(const char* path)
	{
		fragmentShader = getCore()->cacheManager->loadResource<fShader>(path);
		shaderProgram->setfShaderId(fragmentShader->shaderId);
		dirty = true;
	}
	void Renderer::setTexture(const char* path)
	{
		texture = getCore()->cacheManager->loadResource<Texture>(path);
	}
	void Renderer::setModel(const char* path)
	{
		model = getCore()->cacheManager->loadResource<Model>(path);
	}

	glm::mat4 Renderer::getProjectionMat()
	{
		return getCore()->getScreen().lock()->getPerspective(45.0f, 0.1f, 100.0f);
	}
	glm::mat4 Renderer::getModelMat()
	{
		return getEntity()->getComponent<Transform>()->getModelMat();
	}
	std::shared_ptr<Model> Renderer::getModel()
	{
		return getEntity()->getComponent<Model>();
	}
}