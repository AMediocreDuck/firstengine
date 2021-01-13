#ifndef FIRSTENGINE_COLLIDER_H
#define FIRSTENGINE_COLLIDER_H

#include "Component.h"
#include "glm/glm.hpp"

namespace firstengine
{
	struct Collider : Component
	{
		char getColliderType() { return colliderType; }
		bool getDirty() { return dirty; }
		glm::vec3 getCentre() { return centre; }
		glm::vec3 getScale() { return scale; }
		void setCentre(float x, float y, float z);
		void setScale(float x, float y, float z);
		void setScale(float _radius);
		void setTrigger(bool _trigger);


	protected: 
		glm::vec3 centre;
		glm::vec3 scale;
		bool isTrigger;
		char colliderType;
		bool dirty = false;

	};
}

#endif