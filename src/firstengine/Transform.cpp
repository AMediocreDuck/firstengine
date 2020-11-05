#include "Transform.h"
#include <glm/ext.hpp>

namespace firstengine
{
	glm::mat4 Transform::getModelMat()
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, position);
		rotation.y += 0.1;
		//model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f,0.0f,0.0f ));
		model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		
		model = glm::scale(model, scale);
		return model;
	}
}