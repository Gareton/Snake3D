#ifndef TEXTURE_H
#define TEXTURE_H
#include "fileLoader.h"
#include <glad/glad.h>
#include "skTypes.h"
#include "textureSettings.h"

namespace bge
{
	class Texture
	{
	public:
		Texture(sk_uint textureUnit, const Image& image, const TextureSettings& settings);
		~Texture();
		Texture(Texture& o) = delete;
		Texture& operator=(Texture& o) = delete;
		Texture(Texture&& o);
		void use() const;
	private:
		void destructorHelper();

		sk_uint _ID;
		sk_uint _textureUnit;
	};
}

#endif
