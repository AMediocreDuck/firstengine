#include <firstengine/firstEngine.h>

struct Player : public Component
{
	void onTick()
	{
		if (getCore()->getKeyboard()->getKey('a'))
		{
			getTransform()->setPosition(glm::vec3(-3.0f, 0.0f, -10.0f));
		}
	}

};


int main()
{
	std::shared_ptr<Core> core = Core::initialize();
	//EntityOne
	std::shared_ptr<Entity> pe = core->addEntity();
	std::shared_ptr<Renderer> pr = pe->addComponent<Renderer>();
	std::shared_ptr<SoundSource> pss = pe->addComponent<SoundSource>();
	std::shared_ptr<Player> pm = pe->addComponent<Player>();
	pe->getComponent<Transform>()->setPosition(glm::vec3(0.0f,0.0f, -10.0f));
	//pss->setSound("../src/demo/resources/sounds/HeartBeat.ogg");
	//pr->setvShader("../src/firstengine/shaders/VertexShader.txt");
	//pr->setfShader("../src/firstengine/shaders/FragmentShader.txt");
	pr->setShader("../src/firstengine/shaders/VertexShader.txt;../src/firstengine/shaders/FragmentShader.txt");
	pr->setModel("../src/demo/resources/models/curuthers.obj");
	pr->setTexture("../src/demo/resources/textures/Whiskers_diffuse.png");
	//ADD SHADER AS A RESOURCE

	//Entity2
	std::shared_ptr<Entity> pe2 = core->addEntity();
	std::shared_ptr<Renderer> pr2 = pe2->addComponent<Renderer>();
	std::shared_ptr<SoundSource> pss2 = pe2->addComponent<SoundSource>();
	pe2->getComponent<Transform>()->setPosition(glm::vec3(5.0f, 0.0f, -15.0f));
	//pss->setSound("../src/demo/resources/sounds/HeartBeat");
	//pr2->setvShader("../src/firstengine/shaders/VertexShader.txt");
	//pr2->setfShader("../src/firstengine/shaders/FragmentShader.txt");
	pr2->setShader("../src/firstengine/shaders/VertexShader.txt;../src/firstengine/shaders/FragmentShader.txt");
	pr2->setModel("../src/demo/resources/models/curuthers.obj");
	pr2->setTexture("../src/demo/resources/textures/Whiskers_diffuse.png");

	//_core.lock()->loop();
	core->start();

	return 0;
}


