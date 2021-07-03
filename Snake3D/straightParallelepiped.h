#ifndef STRAIGHT_PARALLELEPIPED_H
#define STRAIGHT_PARALLELEPIPED_H
#include "drawable.h"
#include "shader.h"
#include "vertexManager.h"
#include "skTypes.h"
#include <memory>

class StraightParallelepiped : public Drawable 
{
public:
	explicit StraightParallelepiped(const gmt::vec3& size, const gmt::vec3& pos = {}, const gmt::vec3& color = {});

	void draw(const gmt::mat4& projection, const gmt::mat4& view) override;

	void setSize(const gmt::vec3& size);
	void setPos(const gmt::vec3& pos);
	void setColor(const gmt::vec3& color);
private:
	std::unique_ptr<bge::VertexManager> _vertexManager;
	bge::Shader _shader;
	gmt::vec3 _pos;
	gmt::vec3 _color;
	gmt::vec3 _size;
};

#endif
