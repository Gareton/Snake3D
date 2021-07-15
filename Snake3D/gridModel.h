#ifndef GRID_MODEL_H
#define GRID_MODEL_H
#include "skTypes.h"
#include "vertexManager.h"
#include "straightParallelepiped.h"

class GridModel : Drawable
{
public:
	GridModel(const gmt::vec3& pos, sk_uint width, sk_uint height, sk_uint length, 
			  sk_float cellSize, sk_float thickness, const gmt::vec3& color);

	void draw(const gmt::mat4& projection, const gmt::mat4& view) const override;

private:
	gmt::vec3 _pos;
	sk_uint _width, _height, _length;
	sk_float _cellSize;
	sk_float _thickness;
	gmt::vec3 _color;
	mutable bge::StraightParallelepiped _part;
};

#endif
