#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H
#include <string>
#include "gmath.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include "texture.h"
#include "shader.h"
#include "vertexManager.h"
#include "skTypes.h"

class TextRenderer
{
public:
	explicit TextRenderer(const std::string& fontPath);
	void render(const std::string& text, const gmt::mat4 &projection, gmt::vec2 pos = {0.0f, 0.0f},
		 sk_float scale = 1.0f, const gmt::vec3 &color = {0.0f, 1.0f, 0.0f});
private:
	struct Character
	{
		Texture texture;
		VertexManager vertexManager;
		sk_uint advance;

		Character(Texture&& texture_, VertexManager&& vertexManager_, sk_uint advance_)
			: texture(std::move(texture_)), vertexManager(std::move(vertexManager_)), advance(advance_)
		{}
	};

	std::vector<Character> _characters;
	bge::Shader _shader;
};

#endif
