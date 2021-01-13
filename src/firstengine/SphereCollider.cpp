#include "SphereCollider.h"

namespace firstengine
{
	void SphereCollider::onInitialize()
	{
		colliderType = 'S';
		scale = glm::vec3(1.0f);
		isTrigger = false;
		dirty = true;
	}


	
}