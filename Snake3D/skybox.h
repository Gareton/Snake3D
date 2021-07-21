#ifndef SKYBOX_H
#define SKYBOX_H
#include <string>
#include "drawable.h"
#include "vertexManager.h"
#include "shader.h"
#include "fileLoader.h"

class Skybox : public Drawable
{
public:
	Skybox(const std::string& path);
	
	void draw(const gmt::mat4& projection, const gmt::mat4& view) const override;
private:
	std::vector<Image> cutSkyboxImage(const Image& skybox);

	bge::VertexManager _vertexManager;
	bge::Shader _shader;
	sk_uint _texID;
};

#endif

