#include "Renderer.h"
#include <string>
#include <glm/glm.hpp>

namespace firstengine
{
	void Renderer::onInitialize()
	{
		const char* src =
			"\n#ifdef VERTEX\n " \
			"attribute vec2 a_Position; " \
			" " \
			"void main() " \
			"{ " \
			" gl_Position = vec4(a_Position, 0, 1); " \
			"} " \
			" " \
			"\n#endif\n " \
			"\n#ifdef FRAGMENT\n " \
			" " \
			"void main() " \
			"{ " \
			" gl_FragColor = vec4(1, 0, 0, 1); " \
			"} " \
			" " \
			"\n#endif\n ";
		shader = context->createShader();
		shader->parse(src);

		shape = context->createBuffer();
		shape->add(vec2(0, 0.5f));
		shape->add(vec2(-0.5f, -0.5f));
		shape->add(vec2(0.5f, -0.5f));

	}
	void Renderer::onRender()
	{
		shader->setAttribute("a_Position", shape);
		shader->render();

	}
}