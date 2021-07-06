#include "gridModel.h"

GridModel::GridModel(const gmt::vec3& pos, sk_uint width, sk_uint height, sk_uint length,
					 sk_float cellSize, sk_float thickness, const gmt::vec3& color)
	: _pos(pos), _width(width), _height(height), _length(length), _cellSize(cellSize), 
	  _thickness(thickness), _color(color), _part({}, {}, color)
{}

void GridModel::draw(const gmt::mat4& projection, const gmt::mat4& view)
{
	gmt::vec3 origin = _pos - gmt::vec3(gmt::vec3ui{ _width, _height, _length }) * _cellSize * 0.5f;

	// cubes
	_part.setColor(gmt::vec3(0.4f, 0.4f, 0.4f));
	_part.setSize(gmt::vec3(_thickness * 4.0f));

	for (sk_uint x = 0; x <= _width; ++x)
		for (sk_uint y = 0; y <= _height; ++y)
			for (sk_uint z = 0; z <= _length; ++z)
			{
				_part.setPos(origin + gmt::vec3(gmt::vec3ui(x, y, z)) * _cellSize);
				_part.draw(projection, view);
			}

	_part.setColor({});
			
	// x parallel planks 

	_part.setSize({ _cellSize, _thickness, _thickness });

	for(sk_uint x = 0; x < _width; ++x)
		for(sk_uint y = 0; y <= _height; ++y)
			for (sk_uint z = 0; z <= _length; ++z)
			{
				_part.setPos(origin + gmt::vec3(gmt::vec3ui(x, y, z)) * _cellSize 
							 + gmt::vec3(_cellSize * 0.5f, 0.0f, 0.0f));

				_part.draw(projection, view);
			}

	// y parallel planks

	_part.setSize({ _thickness, _cellSize, _thickness });

	for (sk_uint x = 0; x <= _width; ++x)
		for (sk_uint y = 0; y < _height; ++y)
			for (sk_uint z = 0; z <= _length; ++z)
			{
				_part.setPos(origin + gmt::vec3(gmt::vec3ui(x, y, z)) * _cellSize
							 + gmt::vec3(0.0f, _cellSize * 0.5f, 0.0f));

				_part.draw(projection, view);
			}

	// z parallel planks

	_part.setSize({ _thickness, _thickness, _cellSize });

	for (sk_uint x = 0; x <= _width; ++x)
		for (sk_uint y = 0; y <= _height; ++y)
			for (sk_uint z = 0; z < _length; ++z)
			{
				_part.setPos(origin + gmt::vec3(gmt::vec3ui(x, y, z)) * _cellSize
					         + gmt::vec3(0.0f, 0.0f, _cellSize * 0.5f));

				_part.draw(projection, view);
			}
}