#include "cube.h"

Cube::Cube(sk_float size, const gmt::vec3& position, const gmt::vec4& color)
	: _cube({ size, size, size }, position, color)
{}

void Cube::draw(const gmt::mat4& projection, const gmt::mat4& view)
{
	_cube.draw(projection, view);
}

void Cube::update(sk_double deltaTime) {}

void Cube::setPosition(const gmt::vec3& position)
{
	_cube.setPosition(position);
}

void Cube::setColor(const gmt::vec4& color)
{
	_cube.setColor(color);
}