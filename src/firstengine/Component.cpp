#include "Component.h"
#include "Entity.h"

namespace firstengine
{
	void Component::tick()
	{
		onTick();
	}
	void Component::onTick() {};

	void Component::render()
	{
		onRender();
	}
	void Component::onRender()
	{

	}

	std::shared_ptr<Entity> Component::getEntity()
	{
		return entity.lock();
	}
	std::shared_ptr<Core> Component::getCore()
	{
		return getEntity()->getCore();
	}
}