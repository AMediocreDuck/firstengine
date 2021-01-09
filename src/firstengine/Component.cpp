#include "Component.h"
#include "Entity.h"
#include "Transform.h"

namespace firstengine
{
	void Component::tick()
	{
		onSpeedTick();
		onTick();
		onSlowTick();
	}
	void Component::onSpeedTick() {};
	void Component::onTick() {};
	void Component::onSlowTick() {};

	void Component::afterTick()
	{
		onAfterTick();
	}

	void Component::onAfterTick() {};

	void Component::render()
	{
		onRender();
	}
	void Component::onRender()
	{

	}

	void Component::destroy()
	{
		onDestroy();
	}
	void Component::onDestroy()
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
	std::shared_ptr<Transform> Component::getTransform()
	{
		return getEntity()->getComponent<Transform>();
	}
}