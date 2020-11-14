#ifndef FEGRAPHICS_CONTEXT_H
#define FEGRAPHICS_CONTEXT_H

#include <memory>

namespace fegraphics
{
	struct ShaderProgram;
	struct Texture;
	struct Model;
	struct Context
	{
		static std::shared_ptr<Context> initialize();
		std::shared_ptr<ShaderProgram> createShader();
		std::shared_ptr<Texture> createTexture();
		std::shared_ptr<Model> createModel();

	private:
		std::weak_ptr<Context> self;

	};
}

#endif
