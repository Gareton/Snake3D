#include "menuQuad.h"
#include "fileLoader.h"

sk_float ndc(sk_float screenCoord)
{
	return screenCoord * 2.0f - 1.0f;
}

MenuQuad::MenuQuad(const std::string& texturePath, const gmt::vec2& ldPos, const gmt::vec2& ruPos)
	: _vertexManager({ndc(ldPos.x), ndc(ruPos.y), 0.0f, 1.0f,
				      ndc(ruPos.x), ndc(ruPos.y), 1.0f, 1.0f,
					  ndc(ruPos.x), ndc(ldPos.y), 1.0f, 0.0f,
					  ndc(ldPos.x), ndc(ldPos.y), 0.0f, 0.0f }, { 2, 2 }, {0, 1, 2, 0, 3, 2}),
	  _shader(FLoader::loadText("shaders/menuQuad.vs"), FLoader::loadText("shaders/menuQuad.fs")),
	  _texture(0, FLoader::loadImage(texturePath), bge::TextureSettings(GL_TEXTURE_2D, 4))
{}

void MenuQuad::render()
{
	_shader.use();
	_shader.setUniform("tex", sk_int(0));

	_texture.use();

	_vertexManager.draw();
}