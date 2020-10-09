#include "Core.h"
#include "Entity.h"

namespace firstengine
{
	std::shared_ptr<Core> Core::initialize()
	{
		std::shared_ptr<Core> rtn = std::make_shared<Core>();
		rtn->self = rtn;
		return rtn;
	}
	std::shared_ptr<Entity> Core::addEntity()
	{
		std::shared_ptr <Entity> rtn = std::make_shared <Entity>();
		rtn->core = self;
		entities.push_back(rtn);
		return rtn;
	}

	void Core::start()
	{
		for (size_t ei = 0; ei < entities.size(); ei++)
		{
			entities.at(ei)->tick();
		}
	}
}