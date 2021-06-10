#include "grid.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "file_loader.h"

Grid::Grid(const gmt::vec3& position, sk_float cubeSize,
	sk_uint width, sk_uint height, sk_uint length,
	sk_float thickness, const gmt::vec4& color)

	:_position(position), _cubeSize(cubeSize),
	_width(width), _height(height), _length(length),
	_thickness(thickness), _color(color),
	_shader("shaders/gridShader.vs", "shaders/gridShader.fs")
{	
	for (sk_uint z = 0; z <= length; ++z)
		for (sk_uint y = 0; y <= height; ++y)
			addLine(gmt::vec3{ 0.0f, 1.0f * y, 1.0f * z } * cubeSize, 
				    gmt::vec3{ 1.0f * width, 1.0f * y, 1.0f * z } * cubeSize);

	for (sk_uint z = 0; z <= length; ++z)
		for (sk_uint x = 0; x <= width; ++x)
			addLine(gmt::vec3{ 1.0f * x, 0.0f, 1.0f * z } * cubeSize,
				gmt::vec3{ 1.0f * x, 1.0f * height, 1.0f * z } * cubeSize);

	for (sk_uint x = 0; x <= width; ++x)
		for (sk_uint y = 0; y <= height; ++y)
			addLine(gmt::vec3{ 1.0f * x, 1.0f * y, 0.0f} * cubeSize,
				gmt::vec3{ 1.0f * x, 1.0f * y, 1.0f * length } * cubeSize);

	_centerPosition = gmt::vec3{ 0.5f * width, 0.5f * height, 0.5f * length } * cubeSize;

	std::vector<sk_uint> attributeCounts = {3, 2, 1};

	_vertexManager.init(_verticies, _indicies, attributeCounts);
}

void Grid::draw(const gmt::mat4& projection, const gmt::mat4& view)
{
	gmt::mat4 model(1.0f);

	model *= gmt::translate(_position);
	model *= gmt::translate(-_centerPosition);

	_shader.use();
	_shader.setUniform("model", model);
	_shader.setUniform("view", view);
	_shader.setUniform("proj", projection);
	_vertexManager.draw();
}

void Grid::update(sk_double deltaTime)
{

}

sk_float Grid::getCubeSize() const
{
	return _cubeSize;
}

gmt::vec3i Grid::worldToGridCoordinate(gmt::vec3 coord) const
{
	sk_float halfCubeSize = _cubeSize * 0.5f;
	coord -= getOrigin();
	sk_int x = (coord.x - halfCubeSize) / _cubeSize;
	sk_int y = (coord.y - halfCubeSize) / _cubeSize;
	sk_int z = (coord.z - halfCubeSize) / _cubeSize;

	return gmt::vec3i{ x, y, z };
}

gmt::vec3 Grid::gridToWorldCoordinate(const gmt::vec3i& coord) const
{
	gmt::vec3 worldCoord = gmt::vec3{ 1.0f * coord.x, 1.0f * coord.y, 1.0f * coord.z } * _cubeSize + 
						   gmt::vec3{_cubeSize, _cubeSize, _cubeSize} * 0.5f;

	worldCoord += getOrigin();

	return worldCoord;
}

gmt::vec3 Grid::getOrigin() const
{
	return _position - _centerPosition;
}

sk_float Grid::getWidth() const
{
	return _width;
}

sk_float Grid::getHeight() const
{
	return _height;
}

sk_float Grid::getLength() const
{
	return _length;
}

bool Grid::isInside(const gmt::vec3i& coord) const
{
	return gmt::inRange(coord.x, 0, (int)_width)  && 
		   gmt::inRange(coord.y, 0, (int)_height) && 
		   gmt::inRange(coord.z, 0, (int)_length);
}

void Grid::addLine(const gmt::vec3& p1, const gmt::vec3& p2)
{
	if (p1.x != p2.x)
		addXLine(p1, p2);
	else if (p1.y != p2.y)
		addYLine(p1, p2);
	else
		addZLine(p1, p2);
}

void Grid::addXLine(const gmt::vec3& p1, const gmt::vec3& p2)
{
	for(sk_int i = -1; i <= 1; i += 2)
	{
		gmt::vec3 rectanglePoint1(p1.x, p1.y + i * _thickness, p1.z + _thickness);
		gmt::vec3 rectanglePoint2(p2.x, p1.y + i * _thickness, p1.z - _thickness);

		addRectangle(rectanglePoint1, rectanglePoint2);

		rectanglePoint1 = { p1.x, p1.y + _thickness, p1.z + i * _thickness };
		rectanglePoint2 = { p2.x, p1.y - _thickness, p1.z + i * _thickness };

		addRectangle(rectanglePoint1, rectanglePoint2);
	}

	gmt::vec3 rectanglePoint1(p1.x, p1.y + _thickness, p1.z + _thickness);
	gmt::vec3 rectanglePoint2(p1.x, p1.y - _thickness, p1.z - _thickness);

	addRectangle(rectanglePoint1, rectanglePoint2);

	rectanglePoint1 = { p2.x, p1.y + _thickness, p1.z + _thickness };
	rectanglePoint2 = { p2.x, p1.y - _thickness, p1.z - _thickness };

	addRectangle(rectanglePoint1, rectanglePoint2);
}

void Grid::addYLine(const gmt::vec3& p1, const gmt::vec3& p2)
{
	for (sk_int i = -1; i <= 1; i += 2)
	{
		gmt::vec3 rectanglePoint1(p1.x + i * _thickness, p1.y, p1.z + _thickness);
		gmt::vec3 rectanglePoint2(p1.x + i * _thickness, p2.y, p1.z - _thickness);

		addRectangle(rectanglePoint1, rectanglePoint2);

		rectanglePoint1 = { p1.x + _thickness, p1.y, p1.z + i * _thickness };
		rectanglePoint2 = { p1.x - _thickness, p2.y, p1.z + i * _thickness };

		addRectangle(rectanglePoint1, rectanglePoint2);
	}

	gmt::vec3 rectanglePoint1(p1.x + _thickness, p1.y, p1.z + _thickness);
	gmt::vec3 rectanglePoint2(p1.x - _thickness, p1.y, p1.z - _thickness);

	addRectangle(rectanglePoint1, rectanglePoint2);

	rectanglePoint1 = { p2.x + _thickness, p2.y, p1.z + _thickness };
	rectanglePoint2 = { p2.x - _thickness, p2.y, p1.z - _thickness };

	addRectangle(rectanglePoint1, rectanglePoint2);
}

void Grid::addZLine(const gmt::vec3& p1, const gmt::vec3& p2)
{
	for (sk_int i = -1; i <= 1; i += 2)
	{
		gmt::vec3 rectanglePoint1(p1.x + _thickness, p1.y + i * _thickness, p1.z);
		gmt::vec3 rectanglePoint2(p1.x - _thickness, p1.y + i * _thickness, p2.z);

		addRectangle(rectanglePoint1, rectanglePoint2);

		rectanglePoint1 = { p1.x + i * _thickness, p1.y + _thickness, p1.z};
		rectanglePoint2 = { p1.x + i * _thickness, p1.y - _thickness, p2.z};

		addRectangle(rectanglePoint1, rectanglePoint2);
	}

	gmt::vec3 rectanglePoint1(p1.x + _thickness, p1.y + _thickness, p1.z);
	gmt::vec3 rectanglePoint2(p1.x - _thickness, p1.y - _thickness, p1.z);

	addRectangle(rectanglePoint1, rectanglePoint2);

	rectanglePoint1 = { p2.x + _thickness, p1.y + _thickness, p2.z};
	rectanglePoint2 = { p2.x + _thickness, p1.y - _thickness, p2.z};

	addRectangle(rectanglePoint1, rectanglePoint2);
}

void Grid::addVertex(const gmt::vec3& p, const gmt::vec2& borderCoord, sk_float ratio)
{
	_verticies.push_back(p.x);
	_verticies.push_back(p.y);
	_verticies.push_back(p.z);
	_verticies.push_back(borderCoord.x);
	_verticies.push_back(borderCoord.y);
	_verticies.push_back(ratio);
	_indicies.push_back(_indicies.size());
}

void Grid::addRectangle(const gmt::vec3& p1, const gmt::vec3& p2)
{
	gmt::vec3 p3;
	gmt::vec3 p4;

	sk_float len1 = 1.0f;
	sk_float len2 = 1.0f;

	if (p1.x == p2.x)
	{
		p3 = { p1.x, p1.y, p2.z };
		p4 = { p1.x, p2.y, p1.z };
		len1 = abs(p1.y - p2.y);
		len2 = abs(p1.z - p2.z);
	}
	else if (p1.y == p2.y)
	{
		p3 = { p1.x, p1.y, p2.z };
		p4 = { p2.x, p1.y, p1.z };
		len1 = abs(p1.x - p2.x);
		len2 = abs(p1.z - p2.z);
	}
	else
	{
		p3 = { p1.x, p2.y, p1.z };
		p4 = { p2.x, p1.y, p1.z };
		len1 = abs(p1.y - p2.y);
		len2 = abs(p1.x - p2.x);
	}

	if (len1 < len2)
		std::swap(len1, len2);

	sk_float ratio = len2 / len1;

	addVertex(p1, {0.0f, 0.0f}, ratio);
	addVertex(p2, {1.0f, 1.0f}, ratio);
	addVertex(p3, {1.0f, 0.0f}, ratio);
	addVertex(p1, {0.0f, 0.0f}, ratio);
	addVertex(p2, {1.0f, 1.0f}, ratio);
	addVertex(p4, {0.0f, 1.0f}, ratio);
}