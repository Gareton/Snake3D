#include "texture.h"

const std::vector<GLenum> Texture::_textureTypes = {
	GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2,
	GL_TEXTURE3, GL_TEXTURE4, GL_TEXTURE5,
	GL_TEXTURE6, GL_TEXTURE7, GL_TEXTURE8,
	GL_TEXTURE7, GL_TEXTURE8, GL_TEXTURE9,
	GL_TEXTURE10, GL_TEXTURE11, GL_TEXTURE12,
	GL_TEXTURE13, GL_TEXTURE14, GL_TEXTURE15 };

Texture::Texture(const Image& image, size_t textureNumber, int32_t internalFormat,
				 int32_t wrapX, int32_t wrapY, int32_t minFilter, int32_t magFilter)
	: _textureNumber(textureNumber)
{
	GLuint id = 0;

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapX);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapY);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	GLenum format = GL_RGB;

	if (image.channelsCount == 1)
		format = GL_RED;
	else if (image.channelsCount == 2)
		format = GL_RG;
	else if (image.channelsCount == 4)
		format = GL_RGBA;

	const unsigned char *dataPtr = nullptr;

	if (!image.data.empty())
		dataPtr = &image.data[0];

	glTexImage2D(GL_TEXTURE_2D,
		0,
		internalFormat,
		static_cast<GLuint>(image.width),
		static_cast<GLuint>(image.height),
		0,
		format,
		GL_UNSIGNED_BYTE,
		dataPtr);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	_ID = id;
}

Texture::Texture(Texture&& o)
{
	_ID = o._ID;
	_textureNumber = o._textureNumber;
	o._ID = 0;
	o._textureNumber = 0;
}


void Texture::activate()
{
	glActiveTexture(_textureTypes[_textureNumber]);
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, _ID);
}