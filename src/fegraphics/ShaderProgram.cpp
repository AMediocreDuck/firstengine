#include "ShaderProgram.h"
#include <GL/glew.h> // GLuint
#include <glm/ext.hpp> //glm::perspective etc
#include <iostream>
#include <fstream>
#include <string>
#include "fegraphics/Exception.h"

#include "Texture.h"



namespace fegraphics
{

	ShaderProgram::ShaderProgram()
	{

	}
	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(programId);
	}
	//void ShaderProgram::setShaders(const char* vShader, const char* fShader)//const char* vertexPath, const char* fragmentPath)
	//{
	//	vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	//	glShaderSource(vertexShaderId, 1, &vShader, NULL);
	//	glCompileShader(vertexShaderId);
	//	GLint success = 0;
	//	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
	//	if (!success)
	//	{
	//		throw firstengine::Exception("Cannot compile vertex shader");
	//	}

	//	fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	//	glShaderSource(fragmentShaderId, 1, &fShader, NULL);
	//	glCompileShader(fragmentShaderId);
	//	GLint success = 0;
	//	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
	//	if (!success)
	//	{
	//		throw firstengine::Exception("Cannot compile vertex shader");
	//	}
	//	detachShader();
	//}

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

	//void ShaderProgram::uploadModelMatrix(glm::mat4 model)
	//{
	//	setUniform("u_Model", model);
	//}

	//void ShaderProgram::uploadViewMatrix(glm::mat4 view)
	//{
	//	setUniform("u_View", view);
	//}

	//void ShaderProgram::uploadProjectionMatrix(glm::mat4 projection)
	//{
	//	setUniform("u_Projection", projection);
	//}

	//void ShaderProgram::uploadNormalMatrix()
	//{
	//	setUniform("u_Normal", normal);
	//}
	void ShaderProgram::setShaders(const char* vShader, const char* fShader) 
	{ 
		GLint success = 0;
		glShaderSource(vertexShaderId, 1, &vShader, NULL);
		glCompileShader(vertexShaderId);
		glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			throw fegraphics::Exception("Cannot compile vertex shader");
		}

		glShaderSource(fragmentShaderId, 1, &fShader, NULL);
		glCompileShader(fragmentShaderId);
		glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			throw fegraphics::Exception("Cannot compile fragment shader");
		}

		glAttachShader(programId, vertexShaderId);
		glAttachShader(programId, fragmentShaderId);

		glBindAttribLocation(programId, 0, "a_Position");
		glBindAttribLocation(programId, 1, "a_TexCoord");
		glBindAttribLocation(programId, 2, "a_Normal");
		glBindAttribLocation(programId, 3, "a_LightMapCoord");
		glBindAttribLocation(programId, 4, "a_Tangent");
		glBindAttribLocation(programId, 5, "a_Bitangent");

		glLinkProgram(programId);
		glGetProgramiv(programId, GL_LINK_STATUS, &success);
		if (!success)
		{
			throw fegraphics::Exception("Can't link shaders");
		}
		detachShader();

	};
	void ShaderProgram::render(GLuint vaoId, size_t numOfVerts, bool depthTest, bool cullFace, bool blend, std::vector<std::shared_ptr<Texture>> _texture)
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
		for (int x = 0; x < _texture.size(); x++)
		{
			glActiveTexture(GL_TEXTURE0 + x);
			glBindTexture(GL_TEXTURE_2D, _texture.at(x)->getId());
		}
		//if (_texture1 != nullptr)
		//{
		//	glActiveTexture(GL_TEXTURE0);
		//	glBindTexture(GL_TEXTURE_2D, _texture1->getId());
		//}

		// Draw 3 vertices (a triangle)
		glDrawArrays(GL_TRIANGLES, 0, numOfVerts);

		for (int x = 0; x < _texture.size(); x++)
		{
			glActiveTexture(GL_TEXTURE0 + x);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, 0);
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