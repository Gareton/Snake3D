#ifndef TEXTURE_SETTINGS_H
#define TEXTURE_SETTINGS_H
#include <glad/glad.h>
#include "skTypes.h"
#include <map>

namespace bge
{
	class TextureSettings
	{
	public:
		explicit TextureSettings(GLenum textureType, sk_uint channelsCount = 3);

		void setSetting(GLenum setting, sk_int value);

		sk_int getSetting(GLenum setting) const;
		sk_int getInternalFormat() const;
	private:
		std::map<GLenum, sk_int> _settingToValue;
		GLenum _textureType;
		GLenum _internalFormat;
	};
}

#endif
