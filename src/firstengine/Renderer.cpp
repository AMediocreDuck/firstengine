#include "Renderer.h"

#include <string>
#include <glm/glm.hpp>
#include "Entity.h"
#include "Core.h"
#include "CacheManager.h"
#include "firstengine/Exception.h"
#include "Screen.h"
#include "Transform.h"
#include "Model.h"
#include "Texture.h"

#include "vShader.h"
#include "fShader.h"




namespace firstengine
{
	void Renderer::onInitialize()
	{
		shaderProgram = getCore()->context->createShader();
		model = getCore()->context->createModel();
		texture = getCore()->context->createTexture();
	}
	void Renderer::onRender()
	{
		if (dirty)
		{
			shaderProgram->setShaders(vertexShader->data.c_str(), fragmentShader->data.c_str() );
			dirty = false;
		}

		glUseProgram(shaderProgram->getProgramId());
		shaderProgram->setUniform("u_Projection", getProjectionMat());
		shaderProgram->setUniform("u_Model", getModelMat());
		//shaderProgram->uploadProjectionMatrix(getProjectionMat());
		//shaderProgram->uploadModelMatrix(getModelMat());
		shaderProgram->render(model->getVao(), model->getNumVerts(), true, true, true, texture);
	}

	void Renderer::setvShader(const char* path)
	{
		vertexShader = getCore()->cacheManager->loadResource<vShader>(path);
		dirty = true;
	}
	void Renderer::setfShader(const char* path)
	{
		fragmentShader = getCore()->cacheManager->loadResource<fShader>(path);
		dirty = true;
	}
	void Renderer::setTexture(const char* path)
	{
		std::shared_ptr<Texture> rtn = getCore()->cacheManager->loadResource<Texture>(path);
		texture->setTextureData(rtn->data, rtn->w, rtn->h);
	}
	void Renderer::setModel(const char* path)
	{
		std::shared_ptr<Model> rtn = getCore()->cacheManager->loadResource<Model>(path);
		model->setModel(rtn->vaoId, rtn->numVerts);
	}

	glm::mat4 Renderer::getProjectionMat()
	{
		return getCore()->getScreen()->getPerspective(45.0f, 0.1f, 100.0f);
	}
	glm::mat4 Renderer::getModelMat()
	{
		return getEntity()->getComponent<Transform>()->getModelMat();
	}
}
