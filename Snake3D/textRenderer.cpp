#include "textRenderer.h"
#include "vertexManager.h"
#include "FileLoader.h"
#include <algorithm>

namespace bge
{
	TextRenderer::TextRenderer(const std::string& fontPath, const gmt::mat4& projection, sk_uint windowWidth, sk_uint windowHeight) noexcept
		: _projection(projection), _windowWidth(windowWidth), _windowHeight(windowHeight),
		  _shader(FLoader::loadText("shaders/textShader.vs"), FLoader::loadText("shaders/textShader.fs"))
	{
		FT_Library freetypeLibrary = nullptr;

		if (FT_Init_FreeType(&freetypeLibrary))
		{
			_errorMessage = "ERROR::TEXT_RENDERER::FREETYPE_INIT_FAILED";
			_isValid = false;
			return;
		}

		FT_Face face = nullptr;

		if (FT_New_Face(freetypeLibrary, fontPath.c_str(), 0, &face))
		{
			FT_Done_FreeType(freetypeLibrary);
			_errorMessage = "ERROR::TEXT_RENDERER::FACE_CREATION_FAILED";
			_isValid = false;
			return;
		}

		FT_Set_Pixel_Sizes(face, 0, 48);

		for (sk_uchar c = 0; c < 128; ++c)
		{
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				FT_Done_Face(face); 
				FT_Done_FreeType(freetypeLibrary);
				_errorMessage = "ERROR::TEXT_RENDERER::CHAR_LOADING_FAILED";
				_isValid = false;
				return;
			}

			sk_uint width = face->glyph->bitmap.width;
			sk_uint height = face->glyph->bitmap.rows;

			bge::Texture texture(0, Image(face->glyph->bitmap.buffer, width, height, 1), bge::TextureSettings(GL_TEXTURE_2D));

			gmt::vec2 bearing = { (sk_float)face->glyph->bitmap_left, (sk_float)face->glyph->bitmap_top };
			gmt::vec2 size = { (sk_float)width, (sk_float)height };

			sk_float xoffset = bearing.x;
			sk_float yoffset = -(size.y - bearing.y);

			std::vector<sk_float> verticies = {
				xoffset,		  yoffset + size.y,	0.0f, 0.0f,
				xoffset + size.x, yoffset + size.y,	1.0f, 0.0f,
				xoffset + size.x, yoffset,			1.0f, 1.0f,
				xoffset,		  yoffset,			0.0f, 1.0f
			};

			std::vector<sk_uint> indicies = { 0, 1, 2, 3, 2, 0 };

			bge::VertexManager vertexManager(verticies, { 2, 2 }, indicies);

			_characters.push_back(Character{ std::move(texture), std::move(vertexManager), size,
								  (sk_uint)face->glyph->advance.x });
		}

		FT_Done_Face(face); 
		FT_Done_FreeType(freetypeLibrary);
	}

	void TextRenderer::render(const std::string& text, gmt::vec2 pos, sk_float scale, const gmt::vec3 &color)
	{
		if (!_isValid)
			throw std::runtime_error(_errorMessage);

		pos.x *= _windowWidth;
		pos.y *= _windowHeight;

		_shader.use();
		_shader.setUniform("proj", _projection);
		_shader.setUniform("color", color);
		_shader.setUniform("texture0", (sk_uint)0);

		for (char c : text)
		{
			gmt::mat4 model(1.0f);
			model *= gmt::translate(gmt::vec3(pos, 0.0f));
			model *= gmt::scale(scale);

			_shader.setUniform("model", model);

			sk_uint ind = *reinterpret_cast<sk_uchar *>(&c);

			Character &character = _characters[ind];

			character.texture.use();
			character.vertexManager.draw();

			pos.x += scale * (character.advance >> 6);
		}
	}

	void TextRenderer::renderMiddle(const std::string& text, gmt::vec2 pos, sk_float scale, const gmt::vec3 &color)
	{
		sk_float length = getTextLength(text, scale) / (sk_float)_windowWidth;
		sk_float height = getTextHeight(text, scale) / (sk_float)_windowHeight;

		render(text, { pos.x - (length * 0.5f), pos.y - (height * 0.5f) }, scale, color);
	}

	void TextRenderer::renderMiddleUp(const std::string& text, gmt::vec2 pos, sk_float scale, const gmt::vec3 &color)
	{
		sk_float length = getTextLength(text, scale) / (sk_float)_windowWidth;
		sk_float height = getTextHeight(text, scale) / (sk_float)_windowHeight;

		render(text, {pos.x - (length * 0.5f), pos.y - height}, scale, color);
	}

	void TextRenderer::renderMiddleDown(const std::string& text, gmt::vec2 pos, sk_float scale, const gmt::vec3 &color)
	{
		sk_float length = getTextLength(text, scale) / (sk_float)_windowWidth;

		render(text, { pos.x - length * 0.5f, pos.y }, scale, color);
	}

	void TextRenderer::renderDownRight(const std::string& text, gmt::vec2 pos, sk_float scale, const gmt::vec3 &color)
	{
		sk_float length = getTextLength(text, scale) / (sk_float)_windowWidth;

		render(text, { pos.x - length, pos.y }, scale, color);
	}

	void TextRenderer::renderUpLeft(const std::string& text, gmt::vec2 pos, sk_float scale, const gmt::vec3 &color)
	{
		sk_float height = getTextHeight(text, scale) / (sk_float)_windowHeight;

		render(text, { pos.x, pos.y - height }, scale, color);
	}

	void TextRenderer::renderUpRight(const std::string& text, gmt::vec2 pos, sk_float scale, const gmt::vec3 &color)
	{
		sk_float length = getTextLength(text, scale) / (sk_float)_windowWidth;
		sk_float height = getTextHeight(text, scale) / (sk_float)_windowHeight;

		render(text, { pos.x - length, pos.y - height }, scale, color);
	}

	sk_float TextRenderer::getTextLength(const std::string& text, sk_float scale) const
	{
		if (!_isValid)
			throw std::runtime_error(_errorMessage);

		sk_float length = 0.0f;

		for(sk_uint i = 0; i < text.size(); ++i)
			if(i + 1 != text.size())
				length += scale * (_characters[*reinterpret_cast<const sk_uchar *>(&text[i])].advance >> 6);
			else
				length += scale * (_characters[*reinterpret_cast<const sk_uchar *>(&text[i])].size.x);

		return length;
	}

	sk_float TextRenderer::getTextHeight(const std::string& text, sk_float scale) const
	{
		if (!_isValid)
			throw std::runtime_error(_errorMessage);

		sk_float height = 0.0f;

		for (char c : text)
			height = std::max(height, _characters[*reinterpret_cast<sk_uchar *>(&c)].size.y);

		return height;
	}

	void TextRenderer::setProjectionMatrix(const gmt::mat4& projection)
	{
		if (!_isValid)
			throw std::runtime_error(_errorMessage);

		_projection = projection;
	}

	void TextRenderer::setWindowSize(sk_uint windowWidth, sk_uint windowHeight)
	{
		if (!_isValid)
			throw std::runtime_error(_errorMessage);

		_windowWidth = windowWidth;
		_windowHeight = windowHeight;
	}
}