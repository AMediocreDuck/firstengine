#ifndef FEGRAPHICS_SHADERPROGRAM_H
#define FEGRAPHICS_SHADERPROGRAM_H

#include <glm/glm.hpp> //glm::mat4
#include <GL/glew.h> // GLuint
#include <memory>
#include <vector>

namespace fegraphics
{
	struct Texture;
	struct Context;
	struct ShaderProgram
	{
		ShaderProgram();// const char* vertexPath, const char* fragmentPath);
		~ShaderProgram();
		GLuint getProgramId() { return programId; }

		//void setShaders(const char* vShader, const char* fShader);//const char* vertexPath, const char* fragmentPath);
		void setShaders(const char* vShader, const char* fShader);
	/*	void setvShaderId(GLuint id) { vertexShaderId = id; };
		void setfShaderId(GLuint id) { fragmentShaderId = id; };*/
		void setUniform(const char* uniform, glm::mat4 value);
		void setUniform(const char* uniform, glm::vec3 value);
		void setUniform(const char* uniform, float value);
		void setUniform(const char* uniform, int value);

		//void uploadModelMatrix(glm::mat4 model);
		//void modelReset() { model = glm::mat4(1.0f); }
		//void modelTranslate(glm::vec3 _direction);
		//void modelRotate(float _angle, glm::vec3 _axis);
		//void modelScale(glm::vec3 _scale);

		//void uploadViewMatrix(glm::mat4 view);
		//void setViewMatrix(glm::vec3 _cameraPos, glm::vec3 _cameraFront, glm::vec3 _cameraUp);
		//glm::mat4 getViewMatrix() { return view; }
		//void resetViewMatrix() { view = glm::mat4(10.0f); }

		//void uploadProjectionMatrix(glm::mat4 projection);
		//void setPerspectiveMatrix(float _angle, float _width, float _height, float _nearPlane, float _farPlane);
		//void setOrthoGraphicalProjectionMatrix(float _xStart, float _xEnd, float _yStart, float _yEnd, float _zStart, float _zEnd);

		//void uploadNormalMatrix();
		//void setNormalMatrix();

		/*void uploadMatrices();

		void resetMatrixes();*/

		void render(GLuint vaoId, size_t numOfVerts, bool depthTest, bool cullFace, bool blend, std::shared_ptr<Texture> _texture1);
		void setBackgroundColour(glm::vec4 _backgroundColour);
		void detachShader();

	private:
		friend struct fegraphics::Context;
		std::shared_ptr<Context> context;
		GLuint programId;
		GLuint vertexShaderId;
		GLuint fragmentShaderId;

		//glm::mat4 model = glm::mat4(1.0f);
		//glm::mat4 view = glm::mat4(1.0f);
		//glm::mat4 projection;
		glm::mat3 normal = glm::mat4(1.0f);


	};
}
#endif
