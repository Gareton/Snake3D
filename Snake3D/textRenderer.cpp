#include "textRenderer.h"
#include "vertexManager.h"

TextRenderer::TextRenderer(const std::string& fontPath)
	: _shader("shaders/textShader.vs", "shaders/textShader.fs") 
{
	FT_Library freetypeLibrary = nullptr;

	if (FT_Init_FreeType(&freetypeLibrary))
		throw std::runtime_error("ERROR::TEXT_RENDERER::FREETYPE_INIT_FAILED");
	
	FT_Face face = nullptr;

	if(FT_New_Face(freetypeLibrary, fontPath.c_str(), 0, &face))
		throw std::runtime_error("ERROR::TEXT_RENDERER::FACE_CREATION_FAILED");

	FT_Set_Pixel_Sizes(face, 0, 48);

	for (unsigned char c = 0; c < 128; ++c)
	{
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			throw std::runtime_error("ERROR::TEXT_RENDERER::CHAR_LOADING_FAILED");

		size_t width = face->glyph->bitmap.width;
		size_t height = face->glyph->bitmap.rows;

		Texture texture(Image(face->glyph->bitmap.buffer, width, height, 1), 0, GL_RED,
			GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE,
			GL_LINEAR, GL_LINEAR);

		gmt::vec2f bearing = {(float_t)face->glyph->bitmap_left, (float_t)face->glyph->bitmap_top};
		gmt::vec2f size = { (float_t)width, (float_t)height };

		float_t xoffset = bearing.x;
		float_t yoffset = -(size.y - bearing.y);

		std::vector<GLfloat> verticies = {
			xoffset,		  yoffset + size.y,	0.0f, 0.0f,
			xoffset + size.x, yoffset + size.y,	1.0f, 0.0f,
			xoffset + size.x, yoffset,			1.0f, 1.0f,
			xoffset,		  yoffset,			0.0f, 1.0f
		};

		std::vector<GLuint> indicies = { 0, 1, 2, 3, 2, 0 };

		VertexManager vertexManager;
		vertexManager.init(verticies, indicies, { 2, 2 });

		_characters.push_back(Character{ std::move(texture), std::move(vertexManager), 
							  (size_t)face->glyph->advance.x});
	}

	FT_Done_Face(face); // memory leak due to exceptions....
	FT_Done_FreeType(freetypeLibrary);
}

void TextRenderer::render(const std::string& text, const gmt::mat4 &projection,
	gmt::vec2 pos, float_t scale, const gmt::vec3 &color)
{
	_shader.use();
	_shader.setUniform("proj", projection);
	_shader.setUniform("color", color);
	_shader.setUniform("texture0", (GLuint)0);

	for (char c : text)
	{
		gmt::mat4 model(1.0f);
		model *= gmt::translate(gmt::vec3(pos.x, pos.y, 0.0f));
		model *= gmt::scale(scale);

		_shader.setUniform("model", model);

		size_t ind = *reinterpret_cast<unsigned char *>(&c);

		Character &character = _characters[ind];

		character.texture.bind();
		character.texture.activate();

		character.vertexManager.draw();

		pos.x += scale * (character.advance >> 6);
	}
}