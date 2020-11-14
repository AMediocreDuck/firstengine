#include "Transform.h"
#include <glm/ext.hpp>

namespace firstengine
{
	void Transform::onInitialize()
	{
		scale = glm::vec3(1.0f);
		rotation = glm::vec3(0.0f);
		position = glm::vec3(0.0f);
	}

	glm::mat4 Transform::getModelMat()
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, position);
		rotation.y += 0.001;
		model = glm::rotate(model, rotation.x, glm::vec3(1.0f,0.0f,0.0f));
		model = glm::rotate(model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));;
		model = glm::rotate(model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
		
		model = glm::scale(model, scale);
		return model;
	}

	void Transform::setPosition(glm::vec3 _position)
	{
		position = _position;
	}
	void Transform::setRotation(glm::vec3 _rotation)
	{
		rotation = _rotation;
	}
	void Transform::setScale(glm::vec3 _scale)
	{
		scale = _scale;
	}
}