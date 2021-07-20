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
#include <memory>

namespace bge
{
	class TextRenderer
	{
	public:
		TextRenderer(const std::string& fontPath, const gmt::mat4& projection, sk_uint windowWidth, sk_uint windowHeight) noexcept;

		//pos is down left position of text
		// pos.x and pos.y range from 0 to 1
		void render(const std::string& text, gmt::vec2 pos, sk_float scale = 1.0f, const gmt::vec3 &color = gmt::vec3(0.0f));

		// have different pos meaning based on function name
		void renderMiddle(const std::string& text, gmt::vec2 pos, sk_float scale = 1.0f, const gmt::vec3 &color = gmt::vec3(0.0f));
		void renderMiddleUp(const std::string& text, gmt::vec2 pos, sk_float scale = 1.0f, const gmt::vec3 &color = gmt::vec3(0.0f));
		void renderMiddleDown(const std::string& text, gmt::vec2 pos, sk_float scale = 1.0f, const gmt::vec3 &color = gmt::vec3(0.0f));
		void renderDownRight(const std::string& text, gmt::vec2 pos, sk_float scale = 1.0f, const gmt::vec3 &color = gmt::vec3(0.0f));
		void renderUpLeft(const std::string& text, gmt::vec2 pos, sk_float scale = 1.0f, const gmt::vec3 &color = gmt::vec3(0.0f));
		void renderUpRight(const std::string& text, gmt::vec2 pos, sk_float scale = 1.0f, const gmt::vec3 &color = gmt::vec3(0.0f));

		sk_float getTextLength(const std::string& text, sk_float scale = 1.0f) const;
		sk_float getTextHeight(const std::string& text, sk_float scale = 1.0f) const;

		void setProjectionMatrix(const gmt::mat4& projection);
		void setWindowSize(sk_uint windowWidth, sk_uint windowHeight);
	private:
		struct Character
		{
			bge::Texture texture;
			bge::VertexManager vertexManager;
			sk_uint advance;
			gmt::vec2 size;

			Character(bge::Texture&& texture_, bge::VertexManager&& vertexManager_, const gmt::vec2& size_, sk_uint advance_)
				: texture(std::move(texture_)), vertexManager(std::move(vertexManager_)), size(size_), advance(advance_)
			{}
		};

		std::vector<Character> _characters;
		bge::Shader _shader;
		gmt::mat4 _projection;
		sk_uint _windowWidth, _windowHeight;

		bool _isValid = true;
		std::string _errorMessage;
	};
}

#endif
