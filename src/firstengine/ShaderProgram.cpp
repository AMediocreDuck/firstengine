#include "ShaderProgram.h"
#include <GL/glew.h> // GLuint
#include <glm/ext.hpp> //glm::perspective etc
#include <iostream>
#include <fstream>
#include <string>
#include "firstengine/Exception.h"

#include "Texture.h"



namespace firstengine
{
	ShaderProgram::ShaderProgram()//const char* vertexPath, const char* fragmentPath)
	{
		//std::ifstream inFile;
		//std::string shaderCode;
		//std::string line;
		////VERTEX SHADER
		//inFile.open(vertexPath);
		//if (!inFile.is_open())
		//{
		//	throw firstengine::Exception("Cannot Load File");
		//}
		//while (std::getline(inFile, line))
		//{
		//	shaderCode += line;
		//}
		//inFile.close();
		//const char* finishedVShaderCode = shaderCode.c_str();

		//vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
		//glShaderSource(vertexShaderId, 1, &finishedVShaderCode, NULL);
		//glCompileShader(vertexShaderId);
		//GLint success = 0;
		//glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
		//if (!success)
		//{
		//	throw firstengine::Exception("Cannot compile vertex shader");
		//}
		////FRAGMENT SHADER
		//shaderCode = "";
		//inFile.open(fragmentPath);
		//if (!inFile.is_open())
		//{
		//	throw firstengine::Exception("Cannot Load File");
		//}
		//while (std::getline(inFile, line))
		//{
		//	shaderCode += line;
		//}
		//inFile.close();
		//const char* finishedFShaderCode = shaderCode.c_str();

		//fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
		//glShaderSource(fragmentShaderId, 1, &finishedFShaderCode, NULL);
		//glCompileShader(fragmentShaderId);
		//glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);

		//if (!success)
		//{
		//	throw firstengine::Exception("Cannot compile fragment shader");
		//}
		//
		////programId = glCreateProgram();

		//glAttachShader(programId, vertexShaderId);
		//glAttachShader(programId, fragmentShaderId);


		//glBindAttribLocation(programId, 0, "a_Position");

		//glLinkProgram(programId);
		//glGetProgramiv(programId, GL_LINK_STATUS, &success);
		//if (!success)
		//{
		//	throw firstengine::Exception("Cannot get program");
		//}
		//detachShader();
	}


	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(programId);
	}
	void ShaderProgram::setShaders()//const char* vertexPath, const char* fragmentPath)
	{
		//std::ifstream inFile;
		//std::string shaderCode;
		//std::string line;
		////VERTEX SHADER
		//inFile.open(vertexPath);
		//if (!inFile.is_open())
		//{
		//	throw firstengine::Exception("Cannot Load File");
		//}
		//while (std::getline(inFile, line))
		//{
		//	shaderCode += line;
		//}
		//inFile.close();
		//const char* finishedVShaderCode = shaderCode.c_str();

		//vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
		//glShaderSource(vertexShaderId, 1, &finishedVShaderCode, NULL);
		//glCompileShader(vertexShaderId);
		//GLint success = 0;
		//glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
		//if (!success)
		//{
		//	throw firstengine::Exception("Cannot compile vertex shader");
		//}
		////FRAGMENT SHADER
		//shaderCode = "";
		//inFile.open(fragmentPath);
		//if (!inFile.is_open())
		//{
		//	throw firstengine::Exception("Cannot Load File");
		//}
		//while (std::getline(inFile, line))
		//{
		//	shaderCode += line;
		//}
		//inFile.close();
		//const char* finishedFShaderCode = shaderCode.c_str();

		//fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
		//glShaderSource(fragmentShaderId, 1, &finishedFShaderCode, NULL);
		//glCompileShader(fragmentShaderId);
		//glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);

		//if (!success)
		//{
		//	throw firstengine::Exception("Cannot compile fragment shader");
		//}

		glAttachShader(programId, vertexShaderId);
		glAttachShader(programId, fragmentShaderId);

		GLint success;
		glLinkProgram(programId);
		glGetProgramiv(programId, GL_LINK_STATUS, &success);
		if (!success)
		{
			throw firstengine::Exception("Cannot get program");
		}
		detachShader();
	}

	void ShaderProgram::setUniform(const char* uniform, glm::mat4 value)
	{
		GLint matrixLoc = glGetUniformLocation(programId, uniform);
		glUniformMatrix4fv(matrixLoc, 1, GL_FALSE, glm::value_ptr(value));
	}

	void ShaderProgram::setUniform(const char* uniform, glm::vec3 value)
	{
		GLuint uniformLoc = glGetUniformLocation(programId, uniform);
		glUniform3fv(uniformLoc, 1, glm::value_ptr(value));
	}

	void ShaderProgram::setUniform(const char* uniform, float value)
	{
		GLuint uniformLoc = glGetUniformLocation(programId, uniform);
		glUniform1f(uniformLoc, value);
	}

	void ShaderProgram::setUniform(const char* uniform, int value)
	{
		GLuint uniformLoc = glGetUniformLocation(programId, uniform);
		glUniform1i(uniformLoc, value);
	}

	void ShaderProgram::uploadModelMatrix(glm::mat4 model)
	{
		setUniform("u_Model", model);
	}

	//void ShaderProgram::modelTranslate(glm::vec3 _direction)
	//{
	//	model = glm::translate(model, _direction);

	//}

	//void ShaderProgram::modelRotate(float _angle, glm::vec3 _axis)
	//{
	//	model = glm::rotate(model, glm::radians(_angle), _axis);

	//}

	//void ShaderProgram::modelScale(glm::vec3 _scale)
	//{
	//	model = glm::scale(model, _scale);

	//}

	void ShaderProgram::uploadViewMatrix(glm::mat4 view)
	{
		setUniform("u_View", view);
	}

	//void ShaderProgram::setViewMatrix(glm::vec3 _cameraPos, glm::vec3 _cameraFront, glm::vec3 _cameraUp)
	//{
	//	view = glm::lookAt(_cameraPos, _cameraPos + _cameraFront, _cameraUp);

	//}

	void ShaderProgram::uploadProjectionMatrix(glm::mat4 projection)
	{
		setUniform("u_Projection", projection);
	}

	//void ShaderProgram::setPerspectiveMatrix(float _angle, float _width, float _height, float _nearPlane, float _farPlane)
	//{
	//	projection = glm::perspective(glm::radians(_angle),
	//		_width / _height, _nearPlane, _farPlane);

	//}

	//void ShaderProgram::setOrthoGraphicalProjectionMatrix(float _xStart, float _xEnd, float _yStart, float _yEnd, float _zStart, float _zEnd)
	//{
	//	projection = glm::ortho(_xStart, _xEnd, _yStart, _yEnd, _zStart, _zEnd);

	//}

	void ShaderProgram::uploadNormalMatrix()
	{
		setUniform("u_Normal", normal);
	}

	//void ShaderProgram::setNormalMatrix()
	//{
	//	normal = glm::mat3(glm::transpose(glm::inverse(model)));
	//}

	//void ShaderProgram::uploadMatrices()
	//{
	//	setNormalMatrix();
	//	uploadModelMatrix();
	//	uploadViewMatrix();
	//	uploadProjectionMatrix();
	//	uploadNormalMatrix();
	//}

	/*void ShaderProgram::resetMatrixes()
	{
		projection = glm::mat4(1.0f);
		view = glm::mat4(1.0f);
		model = glm::mat4(1.0f);
		normal = glm::mat4(1.0f);

	}*/

	void ShaderProgram::render(GLuint vaoId, size_t numOfVerts, bool depthTest, bool cullFace, bool blend, std::shared_ptr<Texture> _texture1)
	{
		if (depthTest)
		{
			glEnable(GL_DEPTH_TEST);
		}
		if (cullFace)
		{
			glEnable(GL_CULL_FACE);
		}
		if (blend)
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}

		glBindVertexArray(vaoId);

		if (_texture1 != nullptr)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, _texture1->getTextureId());
		}

		// Draw 3 vertices (a triangle)
		glDrawArrays(GL_TRIANGLES, 0, numOfVerts);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);

		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		glDisable(GL_BLEND);
		glUseProgram(0);
	}

	void ShaderProgram::setBackgroundColour(glm::vec4 _backgroundColour)
	{
		glClearColor(_backgroundColour.x, _backgroundColour.y, _backgroundColour.z, _backgroundColour.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void ShaderProgram::detachShader()
	{
		glDetachShader(programId, vertexShaderId);
		glDeleteShader(vertexShaderId);
		glDetachShader(programId, fragmentShaderId);
		glDeleteShader(fragmentShaderId);
	}
}