#ifndef FIRSTENGINE_TRANSFORM_H
#define FIRSTENGINE_TRANSFORM_H

#include <glm/glm.hpp>
#include "Component.h"

namespace firstengine
{
	struct Transform : public Component
	{
		glm::mat4 getModelMat();

	private:
		glm::vec3 position = glm::vec3(0.0f,0.0f,-5.0f);
		glm::vec3 rotation = glm::vec3(1.0f);
		glm::vec3 scale = glm::vec3(1.0f);
	};
}


#endif 
