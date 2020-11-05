#include <firstengine/firstEngine.h>
#include <iostream>
//using namespace firstengine;

int main()
{
	std::shared_ptr<Core> core = Core::initialize();
	std::shared_ptr<Entity> pe = core->addEntity();
	std::shared_ptr<Renderer> pr = pe->addComponent<Renderer>();
	//std::shared_ptr<Model> pm = pe->addComponent<Model>();
	//pm->setModel("../src/demo/resources/models/curuthers.obj");
	pr->setvShader("../src/firstengine/shaders/VertexShader.txt");
	pr->setfShader("../src/firstengine/shaders/FragmentShader.txt");
	pr->setModel("../src/demo/resources/models/curuthers.obj");
	pr->setTexture("../src/demo/resources/textures/Whiskers_diffuse.png");
	//pm->setTexture("../src/demo/resources/textures/Whiskers_diffuse.png");
	//_core.lock()->loop();
	core->start();

	return 0;
}


