#include "grid.h"
#include "settings.h"

Grid::Grid()
	: Grid(Settings::getGridPos(), Settings::getGridWidth(), Settings::getGridHeight(), Settings::getGridLength(),
	  Settings::getGridCubeSize(), Settings::getGridThickness(), Settings::getGridColor())
{
}

Grid::Grid(const gmt::vec3& pos, sk_uint width, sk_uint height, sk_uint length,
		   sk_float cellSize, sk_float thickness, const gmt::vec3& color)
	: _model(pos, width, height, length, cellSize, thickness, color),
	  _width(width), _height(height), _length(length), _cellSize(cellSize)
{
	_origin = pos - gmt::vec3(gmt::vec3ui{ width, height, length }) * cellSize * 0.5f;
}

void Grid::draw(const gmt::mat4& projection, const gmt::mat4& view)
{
	_model.draw(projection, view);
}

sk_float Grid::getCellSize() const
{
	return _cellSize;
}

sk_uint Grid::getWidth() const
{
	return _width;
}

sk_uint Grid::getHeight() const
{
	return _height;
}

sk_uint Grid::getLength() const
{
	return _length;
}

gmt::vec3 Grid::convertGridPos(const gmt::vec3i& pos) const
{
	return _origin + gmt::vec3(pos) * _cellSize + gmt::vec3(_cellSize * 0.5f);
}