#include "Component.h"
#include "Entity.h"
#include "Transform.h"

namespace firstengine
{

	void Component::speedTick()
	{
		onSpeedTick();
	}
	void Component::tick()
	{
		onTick();
	}
	void Component::onSpeedTick() {};
	void Component::onTick() {};

	void Component::afterTick()
	{
		onAfterTick();
	}

	void Component::onAfterTick() {};

	//void Component::collision() {};

	void Component::onCollision(std::shared_ptr<Entity> Collision) {};

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