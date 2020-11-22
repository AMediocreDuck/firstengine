#include "Shader.h"
#include "CacheManager.h"
#include "Core.h"
#include "vShader.h"
#include "fShader.h"

#include <string>
#include <sstream>


namespace firstengine
{
	Shader::~Shader()
	{

	}

	void Shader::onLoad()
	{
		fegShaderProgram = cache.lock()->getCore()->context->createShader();
		std::stringstream ss(path);
		char  delimeter = ';';
		std::string item;
		std::vector<std::string> splittedStrings;
		while (std::getline(ss, item, delimeter))
		{
			splittedStrings.push_back(item);
		}
		vertShader = cache.lock()->loadResource<vShader>(splittedStrings[0].c_str());
		fragShader = cache.lock()->loadResource<fShader>(splittedStrings[1].c_str());
		fegShaderProgram->setShaders(vertShader->data.c_str(), fragShader->data.c_str());

	}
}