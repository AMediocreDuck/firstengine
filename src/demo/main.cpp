#include <firstengine/firstEngine.h>

struct Player : public Component
{
	void onTick()
	{
		//getTransform()->setRotation(glm::vec3(0.0f, 5.0f, 0.0f));
		if (getCore()->getKeyboard()->getKey('w'))
		{
			getTransform()->translate(0.0f,0.0f, -0.01f);
		}
		if (getCore()->getKeyboard()->getKey('s'))
		{
			getTransform()->translate(0.0f, 0.0f, 0.01f);
		}
		if (getCore()->getKeyboard()->getKey('a'))
		{
			getTransform()->translate(-0.01f, 0.0f, 0.0f);
		}
		if (getCore()->getKeyboard()->getKey('d'))
		{
			getTransform()->translate(0.01f, 0.0f, 0.0f);
		}
		if (getCore()->getKeyboard()->getKey('e'))
		{
			getTransform()->translate(0.0f, 0.01f, 0.0f);
		}
		if (getCore()->getKeyboard()->getKey('q'))
		{
			getTransform()->translate(0.0f, -0.01f, 0.0f);
		}
		if (getCore()->getKeyboard()->getKey('k'))
		{
			getTransform()->setRotation(getTransform()->getRotate() + glm::vec3(0.0f, 0.001f, 0.0f));
		}
		if (getCore()->getKeyboard()->getKey('h'))
		{
			getTransform()->setRotation(getTransform()->getRotate() + glm::vec3(0.0f, -0.001f, 0.0f));
		}
		if (getCore()->getKeyboard()->getKey('u'))
		{
			getTransform()->setRotation(getTransform()->getRotate() + glm::vec3(0.001f, 0.0f, 0.0f));
		}
		if (getCore()->getKeyboard()->getKey('j'))
		{
			getTransform()->setRotation(getTransform()->getRotate() + glm::vec3(-0.001f, 0.0f, 0.0f));
		}

	}
};

struct Rotate : public Component
{
	void onTick()
	{
		getTransform()->setRotation(getTransform()->getRotate() + glm::vec3(0.0, 1 * getCore()->getDeltaTime(), 0.0));
	}
};


int main()
{
	std::shared_ptr<Core> core = Core::initialize();
	core->setFPS(60);

	//Camera1
	std::shared_ptr<Entity> cam1 = core->addEntity();
	std::shared_ptr<Camera> cc = cam1->addComponent<Camera>();
	std::shared_ptr<Player> cm = cam1->addComponent<Player>();
	cam1->getComponent<Transform>()->setPosition(glm::vec3(1.0f, 0.0f, -5.0f));
	//Camera2
	//std::shared_ptr<Entity> cam2 = core->addEntity();
	//std::shared_ptr<Camera> cc2 = cam2->addComponent<Camera>();
	//cam2->getComponent<Transform>()->setPosition(glm::vec3(0.0f, -5.0f, 0.0f));
	//EntityOne
	std::shared_ptr<Entity> pe = core->addEntity();
	std::shared_ptr<Renderer> pr = pe->addComponent<Renderer>();
	//std::shared_ptr<SoundSource> pss = pe->addComponent<SoundSource>();
	//std::shared_ptr<Player> pm = pe->addComponent<Player>();
	pe->getComponent<Transform>()->setPosition(glm::vec3(0.0f,1.0f, -10.0f));
	std::shared_ptr<RigidBody> prb = pe->addComponent<RigidBody>();
	//pe->getComponent<Transform>()->setScale(glm::vec3(0.1, 0.1, 0.1));
	std::shared_ptr<Rotate> prr = pe->addComponent<Rotate>();
	//pss->setSound("../src/demo/resources/sounds/HeartBeat.ogg");
	pr->setShader("./Resources/shaders/VertexShader.txt;./Resources/shaders/FragmentShader.txt");
	pr->setModel("./Resources/models/better_ball.obj");
	pr->addTexture("./Resources/pbrTextures/narrowbrick1-albedo.png");
	pr->addTexture("./Resources/pbrTextures/narrowbrick1-ao.png");
	pr->addTexture("./Resources/pbrTextures/narrowbrick1-metallic.png");
	pr->addTexture("./Resources/pbrTextures/narrowbrick1-normal.png");
	pr->addTexture("./Resources/pbrTextures/narrowbrick1-roughness.png");
	pr->addTexture("./Resources/pbrTextures/narrowbrick1-height.png");


	////Entity2
	std::shared_ptr<Entity> pe2 = core->addEntity();
	std::shared_ptr<Renderer> pr2 = pe2->addComponent<Renderer>();
	//std::shared_ptr<SoundSource> pss2 = pe2->addComponent<SoundSource>();
	pe2->getComponent<Transform>()->setPosition(glm::vec3(2.0f, 1.0f, -10.0f));
	std::shared_ptr<Rotate> prr2 = pe2->addComponent<Rotate>();
	//pss->setSound("../src/demo/resources/sounds/HeartBeat");
	pr2->setShader("./Resources/shaders/VertexShader.txt;./Resources/shaders/FragmentShader.txt");
	pr2->setModel("./Resources/models/better_ball.obj");
	pr2->addTexture("./Resources/pbrTextures/fp-albedo.png");
	pr2->addTexture("./Resources/pbrTextures/fp-ao.png");
	pr2->addTexture("./Resources/pbrTextures/fp-metallic.png");
	pr2->addTexture("./Resources/pbrTextures/fp-normal.png");
	pr2->addTexture("./Resources/pbrTextures/fp-roughness.png");
	pr2->addTexture("./Resources/pbrTextures/fp-height.png");


	//Entity 3
	std::shared_ptr<Entity> pe3 = core->addEntity();
	std::shared_ptr<Renderer> pr3 = pe3->addComponent<Renderer>();
	pe3->getComponent<Transform>()->setPosition(glm::vec3(0.0f, -1.0f, -10.0f));
	std::shared_ptr<Rotate> prr3 = pe3->addComponent<Rotate>();
	pr3->setShader("./Resources/shaders/VertexShader.txt;./Resources/shaders/FragmentShader.txt");
	pr3->setModel("./Resources/models/better_ball.obj");
	pr3->addTexture("./Resources/pbrTextures/wsm-albedo.png");
	pr3->addTexture("./Resources/pbrTextures/wsm-ao.png");
	pr3->addTexture("./Resources/pbrTextures/wsm-metallic.png");
	pr3->addTexture("./Resources/pbrTextures/wsm-normal.png");
	pr3->addTexture("./Resources/pbrTextures/wsm-roughness.png");
	pr3->addTexture("./Resources/pbrTextures/wsm-height.png");


	//Entity 4
	std::shared_ptr<Entity> pe4 = core->addEntity();
	std::shared_ptr<Renderer> pr4 = pe4->addComponent<Renderer>();
	pe4->getComponent<Transform>()->setPosition(glm::vec3(2.0f, -1.0f, -10.0f));
	std::shared_ptr<Rotate> prr4 = pe4->addComponent<Rotate>();
	pr4->setShader("./Resources/shaders/VertexShader.txt;./Resources/shaders/FragmentShader.txt");
	pr4->setModel("./Resources/models/better_ball.obj");
	pr4->addTexture("./Resources/pbrTextures/wp-albedo.png");
	pr4->addTexture("./Resources/pbrTextures/wp-ao.png");
	pr4->addTexture("./Resources/pbrTextures/wp-metallic.png");
	pr4->addTexture("./Resources/pbrTextures/wp-normal.png");
	pr4->addTexture("./Resources/pbrTextures/wp-roughness.png");
	pr4->addTexture("./Resources/pbrTextures/wp-height.png");


	//Light Spot 
	//std::shared_ptr<Entity> pe5= core->addEntity();
	//std::shared_ptr<Renderer> pr5 = pe5->addComponent<Renderer>();
	//pe5->getComponent<Transform>()->setPosition(glm::vec3(1.0f, 0.0f, -2.0f));
	//pe5->getComponent<Transform>()->setScale(glm::vec3(0.1, 0.1, 0.1));
	//pr5->setShader("./Resources/shaders/VertexShader.txt;./Resources/shaders/FragmentShader.txt");
	//pr5->setModel("./Resources/models/better_ball.obj");
	//pr5->addTexture("./Resources/pbrTextures/narrowbrick1-albedo.png");
	//pr5->addTexture("./Resources/pbrTextures/narrowbrick1-ao.png");
	//pr5->addTexture("./Resources/pbrTextures/narrowbrick1-metallic.png");
	//pr5->addTexture("./Resources/pbrTextures/narrowbrick1-normal.png");
	//pr5->addTexture("./Resources/pbrTextures/narrowbrick1-roughness.png");
	//pr5->addTexture("./Resources/pbrTextures/narrowbrick1-height.png");



	core->start();

	return 0;
}



