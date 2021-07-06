#ifndef GVECTOR2_UTILITIES_H
#define GVECTOR2_UTILITIES_H
#include "gvector.h"

namespace gmt
{
	sk_float angle(vec2 v1, vec2 v2);
	sk_float dot(const vec2& v1, const vec2& v2);
	sk_float cross(const vec2& v1, const vec2& v2);
	sk_float distance(const vec2& p1, const vec2& p2);
	sk_float length(const vec2& v);
	vec2 normalize(const vec2& v);
	vec2 middle(const vec2& p1, const vec2& p2);

	template<typename T>
	vec2_impl<T> abs(const vec2_impl<T>& v)
	{
		return { std::abs(v.x), std::abs(v.y) };
	}

	template<typename T>
	const T* valuePtr(const vec2_impl<T>& v)
	{
		return &v[0];
	}
}

#endif
