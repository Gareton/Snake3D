#include "gvector2_utilities.h"
#include "gutilities.h"
#include <functional>

namespace gmt
{
	sk_float dot(const vec2& v1, const vec2& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	sk_float cross(const vec2& v1, const vec2& v2)
	{
		return v1.x * v2.y - v1.y * v2.x;
	}

	sk_float distance(const vec2& p1, const vec2& p2)
	{
		return gmt::sqrt(sqr(p1.x - p2.x) + sqr(p1.y - p2.y));
	}

	sk_float length(const vec2& v)
	{
		return gmt::sqrt(v.x * v.x + v.y * v.y);
	}

	vec2 normalize(const vec2& v)
	{
		sk_float len = length(v);

		return len == GLF_ZERO ? v : v / len; // TODO: looks weird
	}

	vec2 middle(const vec2& p1, const vec2& p2)
	{
		return p1 + vec2(p1, p2) * 0.5f;
	}
}