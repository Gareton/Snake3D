#ifndef GRID_H
#define GRID_H
#include "gridModel.h"

class Grid : public Drawable
{
public:
	Grid(const gmt::vec3& pos, sk_uint width, sk_uint height, sk_uint length,
		 sk_float cellSize, sk_float thickness, const gmt::vec3& color);

	void draw(const gmt::mat4& projection, const gmt::mat4& view) override;

	sk_float getCellSize() const;
	sk_uint getWidth() const;
	sk_uint getHeight() const;
	sk_uint getLength() const;
	gmt::vec3 convertGridPos(const gmt::vec3i& pos) const;
private:
	GridModel _model;

	gmt::vec3 _origin;
	sk_uint _width;
	sk_uint _height;
	sk_uint _length;
	sk_float _cellSize;
};

#endif
