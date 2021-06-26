#include "texture.h"

namespace bge
{
	const std::vector<GLenum> Texture::_textureIndexTypes = {
	GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2,
	GL_TEXTURE3, GL_TEXTURE4, GL_TEXTURE5,
	GL_TEXTURE6, GL_TEXTURE7, GL_TEXTURE8,
	GL_TEXTURE7, GL_TEXTURE8, GL_TEXTURE9,
	GL_TEXTURE10, GL_TEXTURE11, GL_TEXTURE12,
	GL_TEXTURE13, GL_TEXTURE14, GL_TEXTURE15 };

	Texture::Texture(sk_uint textureIndex, const Image& image, const TextureSettings& settings)
		: _textureIndex(textureIndex)
	{
		glGenTextures(1, &_ID);
		glBindTexture(GL_TEXTURE_2D, _ID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, settings.getSetting(GL_TEXTURE_WRAP_S));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, settings.getSetting(GL_TEXTURE_WRAP_T));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, settings.getSetting(GL_TEXTURE_MIN_FILTER));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, settings.getSetting(GL_TEXTURE_MAG_FILTER));
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		GLenum format = GL_RGB;

		if (image.getChannelsCount() == 1)
			format = GL_RED;
		else if (image.getChannelsCount() == 2)
			format = GL_RG;
		else if (image.getChannelsCount() == 4)
			format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D,
			0,
			settings.getInternalFormat(),
			image.getWidth(),
			image.getHeight(),
			0,
			format,
			GL_UNSIGNED_BYTE,
			image.getDataPtr());

		glGenerateMipmap(GL_TEXTURE_2D);
		glActiveTexture(_textureIndexTypes[_textureIndex]);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture::~Texture()
	{
		destructorHelper();
	}

	Texture::Texture(Texture&& o)
	{
		_ID = o._ID;
		_textureIndex = o._textureIndex;
		o._ID = 0;
	}

	void Texture::use()
	{
		glBindTexture(GL_TEXTURE_2D, _ID);
	}

	void Texture::destructorHelper()
	{
		if (!_ID) return;

		sk_int bindedTexture = 0;

		glGetIntegerv(GL_TEXTURE_BINDING_2D, &bindedTexture);

		if (bindedTexture == _ID)
			glBindTexture(GL_TEXTURE_2D, 0);

		glDeleteTextures(1, &_ID);
	}
}