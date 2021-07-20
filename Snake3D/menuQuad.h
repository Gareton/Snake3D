#ifndef MENU_QUAD_H
#define MENU_QUAD_H
#include "vertexManager.h"
#include "shader.h"
#include "texture.h"
#include <string>

class MenuQuad 
{
public:
	MenuQuad(const std::string& texturePath, const gmt::vec2& ldPos, const gmt::vec2& ruPos);

	void render();
private:
	bge::VertexManager _vertexManager;
	bge::Shader _shader;
	bge::Texture _texture;
};

#endif
