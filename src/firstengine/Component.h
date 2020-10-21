#ifndef FIRSTENGINE_COMPONENT_H
#define FIRSTENGINE_COMPONENT_H
#include <memory>


namespace firstengine
{

	struct Entity;
	struct Component
	{
		friend firstengine::Entity;

		void onInitialize() {};
		void tick();
		virtual void onTick();
		void render();
		virtual void onRender();

	protected:
		std::weak_ptr<Entity> entity;

	};
}
#endif
