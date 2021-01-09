#include "Entity.h"
#include "Component.h"

namespace firstengine
{
	void Entity::tick()
	{
		for (size_t ci = 0; ci < components.size(); ci++)
		{
			components.at(ci)->tick();
		}
	}

	void Entity::afterTick()
	{
		for (size_t ci = 0; ci < components.size(); ci++)
		{
			components.at(ci)->afterTick();
		}
	}
	void Entity::render()
	{
		for (size_t ci = 0; ci < components.size(); ci++)
		{
			components.at(ci)->render();
		}
	}
	std::shared_ptr<Core> Entity::getCore()
	{
		return core.lock();
	}

}