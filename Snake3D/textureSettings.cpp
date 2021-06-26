#include "textureSettings.h"
#include <stdexcept>

namespace bge
{
	TextureSettings::TextureSettings(GLenum textureType, sk_uint channelsCount)
	{
		_textureType = textureType;

		_settingToValue[GL_TEXTURE_WRAP_S] = GL_CLAMP_TO_EDGE;
		_settingToValue[GL_TEXTURE_WRAP_T] = GL_CLAMP_TO_EDGE;
		_settingToValue[GL_TEXTURE_MIN_FILTER] = GL_LINEAR; 
		_settingToValue[GL_TEXTURE_MAG_FILTER] = GL_LINEAR;

		_internalFormat = GL_RGB;

		if (channelsCount == 1)
			_internalFormat = GL_RED;
		else if (channelsCount == 2)
			_internalFormat = GL_RG;
		else if (channelsCount == 4)
			_internalFormat = GL_RGBA;
	}

	void TextureSettings::setSetting(GLenum setting, sk_int value)
	{
		_settingToValue[setting] = value;
	}

	sk_int TextureSettings::getSetting(GLenum setting) const
	{
		auto it = _settingToValue.find(setting);

		if (it == _settingToValue.end())
			throw std::invalid_argument("ERROR::TEXTURE_SETTINGS::GET_SETTING::INVALID_SETTING");

		return it->second;
	}

	sk_int TextureSettings::getInternalFormat() const
	{
		return _internalFormat;
	}
}