#include "cube.h"

namespace bge
{
	Cube::Cube(sk_float size, const gmt::vec3& pos, const gmt::vec3& color)
		: StraightParallelepiped(gmt::vec3(size), pos, color)
	{}

	sk_float Cube::getSize() const
	{
		return StraightParallelepiped::getSize().x;
	}
}