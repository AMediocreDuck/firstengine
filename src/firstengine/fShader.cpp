#include "fShader.h"
#include <fstream>
#include <string>
#include "firstengine/Exception.h"

namespace firstengine
{
	void fShader::onLoad()
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
		//shaderId = glCreateShader(GL_FRAGMENT_SHADER);
		//glShaderSource(shaderId, 1, &data, NULL);
		//glCompileShader(shaderId);
		//GLint success = 0;
		//glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
		//if (!success)
		//{
		//	throw firstengine::Exception("Cannot compile vertex shader");
		//}
	}
}