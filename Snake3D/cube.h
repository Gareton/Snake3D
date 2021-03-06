#ifndef CUBE_H
#define CUBE_H
#include "gmath.h"
#include "drawable.h"
#include "straightParallelepiped.h"
#include "skTypes.h"

namespace bge
{
	class Cube : public StraightParallelepiped
	{
	public:
		explicit Cube(sk_float size, const gmt::vec3& pos = {}, const gmt::vec3& color = {});

		sk_float getSize() const;
	};
}

#endif
