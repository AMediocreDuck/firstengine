#ifndef FIRSTENGINE_COMPONENT_H
#define FIRSTENGINE_COMPONENT_H

namespace firstengine
{
	struct Component
	{
		void tick();
		virtual void onTick();

	private:
	};
}
#endif
