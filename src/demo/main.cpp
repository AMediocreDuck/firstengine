#include <firstengine/firstEngine.h>

#include <iostream>
//using namespace firstengine;

int main()
{
	std::shared_ptr<Core> core = Core::initialize();
	std::shared_ptr<Entity> pe = core->addEntity();
	std::shared_ptr<Renderer> pc = pe->addComponent<Renderer>();

	core->start();

	return 0;
}