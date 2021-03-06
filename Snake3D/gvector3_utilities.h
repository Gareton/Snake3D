#ifndef GVECTOR3_UTILITIES_H
#define GVECTOR3_UTILITIES_H
#include "gvector.h"

namespace gmt
{
	sk_float angle(vec3 v1, vec3 v2);
	sk_float dot(const vec3& v1, const vec3& v2);
	vec3 cross(const vec3& v1, const vec3& v2);
	sk_float distance(const vec3& p1, const vec3& p2);
	sk_float length(const vec3& v);
	vec3 normalize(const vec3& v);
	vec3 normal(const vec3& v1, const vec3& v2);
	vec3 middle(const vec3& p1, const vec3& p2);

	template<typename T>
	vec3_impl<T> abs(const vec3_impl<T>& v)
	{
		return { std::abs(v.x), std::abs(v.y), std::abs(v.z) };
	}

	template<typename T>
	const T* valuePtr(const vec3_impl<T>& v)
	{
		return &v[0];
	}
}

#endif
