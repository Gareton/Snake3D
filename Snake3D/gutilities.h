#ifndef GUTILITIES_H
#define GUTILITIES_H
#include "gvector.h"
#include "gmatrix.h"

namespace gmt
{
	sk_uint random();

	sk_float sqrt(sk_float val);
	sk_float radians(sk_float degrees);
	sk_float fmod(sk_float val, sk_float m);
	sk_float cut(sk_float angle);

	vec2 operator*(const mat2& m, const vec2& v);
	vec3 operator*(const mat3& m, const vec3& v);
	vec4 operator*(const mat4& m, const vec4& v);

	sk_float sin(sk_float angle);
	sk_float cos(sk_float angle);
	sk_float tan(sk_float angle);
	sk_float ctan(sk_float angle);
	sk_float asin(sk_float angle);
	sk_float acos(sk_float angle);
	sk_float atan2(sk_float y, sk_float x);

	const sk_float GLF_ZERO = static_cast<sk_float>(0); // TODO: get rid of it
	const sk_float PI = static_cast<sk_float>(acos(-1.0f));

	template<typename T>
	T clamp(const T& val, const T& lo, const T& hi)
	{
		if (val < lo)
			return lo;
		else if (val > hi)
			return hi;

		return val;
	}

	template<typename T>
	bool inRange(const T& val, const T& lo, const T& hi) // half interval [lo; hi)
	{
		return val >= lo && val < hi;
	}

	template<typename T>
	T sqr(const T& val)
	{
		return val * val;
	}
}

#endif
