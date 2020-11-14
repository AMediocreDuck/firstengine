#ifndef FIRSTENGINE_COMPONENT_H
#define FIRSTENGINE_COMPONENT_H
#include <memory>


namespace firstengine
{
	struct Core;
	struct Entity;
	struct Transform;
	struct Component
	{
		friend struct firstengine::Entity;

		void onInitialize() {};
		void tick();
		virtual void onTick();
		void render();
		virtual void onRender();
		void destroy();
		virtual void onDestroy();
		std::shared_ptr<Core> getCore();
		std::shared_ptr<Entity> getEntity();
		std::shared_ptr<Transform> getTransform();



	private:
		std::weak_ptr<Entity> entity;

	};
}
#endif
