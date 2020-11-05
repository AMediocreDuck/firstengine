#ifndef FIRSTENGINE_CONTEXT_H
#define FIRSTENGINE_CONTEXT_H

#include <memory>

namespace firstengine
{
	struct ShaderProgram;
	struct Texture;
	struct Context
	{
		static std::shared_ptr<Context> initialize();
		std::shared_ptr<ShaderProgram> createShader();
		std::shared_ptr<Texture> createTexture();
		//std::shared_ptr<Buffer> createBuffer();

	private:
		std::weak_ptr<Context> self;

	};
}

#endif
