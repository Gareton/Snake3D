#ifndef TEXTURE_H
#define TEXTURE_H
#include "fileLoader.h"
#include <glad/glad.h>
#include "skTypes.h"

class Texture 
{
public:
	Texture(const Image& image, sk_uint textureNumber, sk_int internalFormat = GL_RGB,
		    sk_int wrapX = GL_REPEAT, sk_int wrapY = GL_REPEAT,
		    sk_int minFilter = GL_NEAREST_MIPMAP_NEAREST,
			sk_int magFilter = GL_NEAREST);
	//~Texture();
	Texture(Texture& o) = delete;
	Texture& operator=(Texture& o) = delete;
	Texture(Texture&& o);
	void activate();
	void bind();
private:
	static const std::vector<GLenum> _textureTypes;
	sk_uint _ID;
	sk_uint _textureNumber;
};

#endif
