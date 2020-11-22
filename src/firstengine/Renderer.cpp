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

#include "Shader.h"
#include "vShader.h"
#include "fShader.h"

#include "Camera.h"




namespace firstengine
{
	void Renderer::onInitialize()
	{

	}
	void Renderer::onRender()
	{
		glUseProgram(shaderProgram->fegShaderProgram->getProgramId());
		shaderProgram->fegShaderProgram->setUniform("u_Projection", getProjectionMat());
		shaderProgram->fegShaderProgram->setUniform("u_Model", getModelMat());
		shaderProgram->fegShaderProgram->setUniform("u_View", getCore()->getActiveCamera()->getViewMatrix());
		shaderProgram->fegShaderProgram->render(model->fegModel->getVao(), model->fegModel->getNumVerts(), true, true, true, texture->fegTexture);
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
		texture = getCore()->cacheManager->loadResource<Texture>(path);
		//texture->setTextureData(rtn->data, rtn->w, rtn->h);
	}
	void Renderer::setModel(const char* path)
	{
		std::shared_ptr<Model> rtn = getCore()->cacheManager->loadResource<Model>(path);
		//model->setModel(rtn->vaoId, rtn->numVerts);
		model = rtn;
	}
	void Renderer::setShader(const char* path)
	{
		std::shared_ptr<Shader> rtn = getCore()->cacheManager->loadResource<Shader>(path);
		//model->setModel(rtn->vaoId, rtn->numVerts);
		shaderProgram = rtn;
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
