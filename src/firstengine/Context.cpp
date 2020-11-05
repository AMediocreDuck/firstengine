#include "Context.h"
#include "firstengine/Exception.h"
#include "ShaderProgram.h"
#include "Texture.h"

#include <GL/glew.h>
namespace firstengine
{
	std::shared_ptr<Context> Context::initialize()
	{
		std::shared_ptr<Context> rtn = std::make_shared<Context>();

		if (glewInit() != GLEW_OK)
		{
			throw firstengine::Exception("Failed to initialize glew");
		}

		rtn->self = rtn;

		return rtn;
	}
	std::shared_ptr<ShaderProgram> Context::createShader()
	{
		GLuint id = 0;
		id = glCreateProgram();

		if (id == 0)
		{
			throw firstengine::Exception("Failed to create shader program");
		}

		std::shared_ptr<ShaderProgram> rtn = std::make_shared<ShaderProgram>();
		rtn->context = self.lock();
		rtn->programId = id;

		return rtn;
	}

	std::shared_ptr<Texture> Context::createTexture()
	{
		GLuint id;
		glGenTextures(1, &id);

		if (!id)
		{
			throw firstengine::Exception("Failed to set texture Id");
		}

		std::shared_ptr<Texture> rtn = std::make_shared<Texture>();
		rtn->context = self.lock();
		rtn->textureId = id;

		return rtn;
	}

}