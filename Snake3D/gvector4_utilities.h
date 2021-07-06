#ifndef GVECTOR4_UTILITIES_H
#define GVECTOR4_UTILITIES_H
#include "gvector.h"

namespace gmt
{
	template<typename T>
	vec4_impl<T> abs(const vec4_impl<T>& v)
	{
		return { std::abs(v.x), std::abs(v.y), std::abs(v.z), std::abs(v.w) };
	}

	template<typename T>
	const T* valuePtr(const vec4_impl<T>& v)
	{
		return &v[0];
	}
}
#endif
