#ifndef FIRSTENGINE_ENTITY_H
#define FIRSTENGINE_ENTITY_H

#include <vector>
#include <memory>

namespace firstengine
{
	struct Component;
	struct Core;
	struct Entity
	{
		friend struct firstengine::Core;
		template <typename T>
		std::shared_ptr<T> addComponent()
		{
			std::shared_ptr<T> rtn = std::make_shared<T>();
			rtn->entity = self;
			components.push_back(rtn);

			rtn->onInitialize();
			return rtn;
		}
		void tick();
	private:
		std::vector<std::shared_ptr<Component>> components;
		std::weak_ptr<Core> core;
		std::weak_ptr<Entity> self;

	};
}
#endif
