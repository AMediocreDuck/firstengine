#include "vShader.h"
#include <fstream>
#include <string>
#include "firstengine/Exception.h"

namespace firstengine
{
	void vShader::onLoad()
	{
		std::ifstream inFile;
		std::string shaderCode;
		std::string line;
		//VERTEX SHADER
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
		const char* finishedVShaderCode = shaderCode.c_str();

		shaderId = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(shaderId, 1, &finishedVShaderCode, NULL);
		glCompileShader(shaderId);
		GLint success = 0;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			throw firstengine::Exception("Cannot compile vertex shader");
		}
	}
}