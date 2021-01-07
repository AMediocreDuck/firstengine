#ifndef FIRSTENGINE_TRANSFORM_H
#define FIRSTENGINE_TRANSFORM_H

#include <glm/glm.hpp>
#include "Component.h"

namespace firstengine
{
	struct Transform : public Component
	{

		void onInitialize();
		glm::mat4 getModelMat();
		glm::vec3 getPosition() { return position; }
		glm::vec3 getRotate() { return rotation; }
		void translate(float x, float y, float z);
		void rotate(glm::vec3 _speeds);
		void setPosition(glm::vec3 _position);
		void setRotation(glm::vec3 _rotation);
		void setScale(glm::vec3 _scale);

	private:
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
		glm::vec3 direction;
	};
}


#endif 
