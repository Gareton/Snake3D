#ifndef GMATH_H
#define GMATH_H
#include <glad/glad.h>
#include <array>
#include <initializer_list>
#include <iostream>
#include "skTypes.h"
#include <chrono>
#include <random>
#include "gvector.h"
#include "gmatrix.h"


namespace gmt
{
	const sk_float GLF_ZERO = static_cast<sk_float>(0); // TODO: get rid of it
	const sk_float PI = static_cast<sk_float>(acos(-1.0f));

	sk_float dot(const vec2f& v1, const vec2f& v2);
	sk_float dot(const vec3f& v1, const vec3f& v2);

	sk_float cross(const vec2f& v1, const vec2f& v2);
	sk_float cross(const vec2f& v1, const vec2f& v2);

	vec3f crossVector(const vec3f& v1, const vec3f& v2);

	sk_float distance(const vec2f& p1, const vec2f& p2);
	sk_float distance(const vec3f& p1, const vec3f& p2);

	sk_float length(const vec2f& v);
	sk_float length(const vec3f& v);

	vec2f normalize(const vec2f& v);
	vec3f normalize(const vec3f& v);

	vec2f getNormal(const vec2f& p1, const vec2f& p2);
	vec3f getNormal(const vec3f& p1, const vec3f& p2);

	vec2f getMiddle(const vec2f& p1, const vec2f& p2);
	vec3f getMiddle(const vec3f& p1, const vec3f& p2);

	sk_float sqr(sk_float x);

	template<typename T, sk_uint N, sk_uint M>
	std::ostream& operator<<(std::ostream& o, const mat<T, N, M>& m)
	{
		for (sk_uint i = 0; i < N; ++i)
		{
			for (sk_uint j = 0; j < M; ++j)
				o << m.get(i, j) << " ";

			if (i + 1 != N)
				o << std::endl;
		}

		return o;
	}

	std::ostream& operator<<(std::ostream& o, const vec2f& v);
	std::ostream& operator<<(std::ostream& o, const vec3& v);
	std::ostream& operator<<(std::ostream& o, const vec4& v);

	vec2f operator*(const mat2& m, const vec2f& v);
	vec3 operator*(const mat3& m, const vec3& v);
	vec4 operator*(const mat4& m, const vec4& v);

	mat4 translate(const vec3& v);
	mat4 rotateX(sk_float angle);
	mat4 rotateY(sk_float angle);
	mat4 rotateZ(sk_float angle);
	mat4 rotate(sk_float angle, const vec3& v);
	mat4 scale(sk_float scaler);
	mat4 scale(const vec3& v);
	mat4 perspective(sk_float fov, sk_float widthToHeightRatio, sk_float nearPlane, sk_float farPlane);
	mat4 ortho(sk_float minX, sk_float maxX, sk_float minY, sk_float maxY);

	sk_float radians(sk_float degrees);
	sk_float cutAngle(sk_float angle);
	sk_float calcAngle(vec3 v1, vec3 v2);

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

	sk_uint randomUint();
}

#endif