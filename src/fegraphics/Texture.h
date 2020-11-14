#ifndef FEGRAPHICS_TEXTURE_H
#define FEGRAPHICS_TEXTURE_H

#include <memory>
#include <GL/glew.h> // GLuint

namespace fegraphics
{
	struct Context;
	struct Texture
	{
		Texture();
		~Texture();
		void setTextureData(unsigned char* _data, int _w, int _h);
		GLuint getTextureId() { return textureId; }
		GLuint getId();

	private:
		friend struct fegraphics::Context;
		unsigned char* data;
		bool dirty;
		std::shared_ptr<Context> context;
		int texWidth;
		int texHeight;
		GLuint textureId;
	};
}
#endif
