#ifndef STRAIGHT_PARALLELEPIPED_H
#define STRAIGHT_PARALLELEPIPED_H
#include "drawable.h"
#include "shader.h"
#include "vertexManager.h"
#include "skTypes.h"

class StraightParallelepiped : public Drawable 
{
public:
	explicit StraightParallelepiped(const gmt::vec3& size, const gmt::vec3& position = { 0.0f, 0.0f, 0.0f }, 
						   const gmt::vec4& color = {0.0f, 0.0f, 0.0f, 1.0f});

	void draw(const gmt::mat4& projection, const gmt::mat4& view);
	void update(sk_double deltaTime);
	void resize(const gmt::vec3& size);

	void setPosition(const gmt::vec3& position);
	void setColor(const gmt::vec4& color);
private:
	VertexManager _vertexManager;
	Shader _shader;
	gmt::vec3 _position;
	gmt::vec4 _color;
	gmt::vec3 _size;
};

#endif
