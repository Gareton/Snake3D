#ifndef TEXTURE_H
#define TEXTURE_H
#include "file_loader.h"
#include <glad/glad.h>

class Texture // needs destructor
{
public:
	Texture(const Image& image, size_t textureNumber, int32_t internalFormat = GL_RGB,
		    int32_t wrapX = GL_REPEAT, int32_t wrapY = GL_REPEAT,
		    int32_t minFilter = GL_NEAREST_MIPMAP_NEAREST,
			int32_t magFilter = GL_NEAREST);
	Texture(Texture& o) = delete;
	Texture& operator=(Texture& o) = delete;
	Texture(Texture&& o);
	void activate();
	void bind();
private:
	static const std::vector<GLenum> _textureTypes;
	size_t _ID;
	size_t _textureNumber;
};

#endif
