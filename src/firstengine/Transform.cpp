#include "Transform.h"
#include <glm/ext.hpp>

namespace firstengine
{
	void Transform::onInitialize()
	{
		scale = glm::vec3(1.0f);
		rotation = glm::vec3(0.0f);
		position = glm::vec3(0.0f);

		direction.x = cos(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));
		direction.y = sin(glm::radians(rotation.y));
		direction.z = sin(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));
		direction = glm::normalize(direction);
	}

	glm::mat4 Transform::getModelMat()
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, position);
		model = glm::rotate(model, rotation.x, glm::vec3(1.0f,0.0f,0.0f));
		model = glm::rotate(model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));;
		model = glm::rotate(model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
		
		model = glm::scale(model, scale);
		return model;
	}
	void Transform::translate(float x, float y, float z)
	{
		glm::vec4 fwd = getModelMat() * glm::vec4(x, y, z, 0.0f);
		position += glm::vec3(fwd);

	}
	void Transform::setPosition(glm::vec3 _position)
	{
		position = _position;
	}
	void Transform::setRotation(glm::vec3 _rotation)
	{
		//Pitch up and down X 
		//Roll Along the Z
		//Yaw Along Y
		rotation = _rotation;
	}
	void Transform::setScale(glm::vec3 _scale)
	{
		scale = _scale;
	}
}