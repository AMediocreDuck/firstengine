#include "vShader.h"
#include <fstream>
#include "firstengine/Exception.h"

namespace firstengine
{
	void vShader::onLoad()
	{
		std::ifstream inFile;
		std::string shaderCode;
		std::string line;
		inFile.open(path);
		if (!inFile.is_open())
		{
			throw firstengine::Exception("Cannot Load File");
		}
		while (std::getline(inFile, line))
		{
			shaderCode += line;
		}
		inFile.close();
		data = shaderCode;

	}
}