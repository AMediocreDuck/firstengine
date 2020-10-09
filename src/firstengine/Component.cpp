#include "Component.h"

namespace firstengine
{
	void Component::tick()
	{
		onTick();
	}
	void Component::onTick() {};
}