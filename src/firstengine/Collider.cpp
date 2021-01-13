#include "Collider.h"

namespace firstengine
{
	void Collider::setCentre(float x, float y, float z)
	{
		centre = glm::vec3(x, y, z);
		dirty = true;
	}

	void Collider::setTrigger(bool _trigger)
	{
		isTrigger = _trigger;
		dirty = true;
	}

	void Collider::setScale(float x, float y, float z)
	{
		scale = glm::vec3(x, y, z);
	}

	void Collider::setScale(float radius)
	{
		scale = glm::vec3(radius, radius, radius);
	}
}