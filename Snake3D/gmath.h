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
	class mat
	{
	public:
		mat() = default;

		mat(const T(&ar)[N][M])
		{
			for (int i = 0; i < N; ++i)
				for (int j = 0; j < M; ++j)
					_data[i][j] = ar[i][j];
		}

		mat(const T& diagValue)
		{
			static_assert(N == M, "To initialize matrix with diagonal it must be sqare");

			for (int i = 0; i < N; ++i)
				for (int j = 0; j < N; ++j)
					if (i == j)
						_data[i][j] = diagValue;
					else
						_data[i][j] = T();
		}

		mat& operator=(const mat& o) 
		{
			if (this == &o) return *this;

			for (sk_uint i = 0; i < N; ++i)
				for (sk_uint j = 0; j < M; ++j)
					_data[i][j] = o._data[i][j];

			return *this;
		}

		mat operator+(const mat& o) const
		{
			mat rval;

			for (sk_uint i = 0; i < N; ++i)
				for (sk_uint j = 0; j < M; ++j)
					rval[i][j] = _data[i][j] + o._data[i][j];

			return std::move(rval);
		}

		mat operator-() const
		{
			mat rval;

			for (sk_uint i = 0; i < N; ++i)
				for (sk_uint j = 0; j < M; ++j)
					rval[i][j] = -_data[i][j];

			return std::move(rval);
		}

		mat operator-(const mat& o) const
		{
			return std::move(*this + (-o));
		}

		template<sk_uint Q>
		mat<T, N, Q> operator*(const mat<T, M, Q>& o) const
		{
			mat<T, N, Q> rval;

			for (sk_uint i = 0; i < N; ++i)
				for (sk_uint j = 0; j < Q; ++j)
					for (sk_uint k = 0; k < M; ++k)
						rval[i][j] += _data[i][k] * o.get(k, j);
			
			return std::move(rval);
		}

		template<sk_uint Q>
		mat<T, N, Q>& operator*=(const mat<T, M, Q>& o)
		{
			return (*this) = (*this) * o;
		}

		T* operator[](sk_uint row) 
		{
			if (row >= N)
				throw std::runtime_error("gmath.h::mat::operator[]::index_out_of_bounds");

			return _data[row];
		}

		const T& get(sk_uint row, sk_uint col) const
		{
			if (row >= N || col >= M)
				throw std::runtime_error("gmath.h::mat::get::index_out_of_bounds");

			return _data[row][col];
		}

	private:
		T _data[N][M] = {};
	};

	using mat2f = mat<sk_float, 2, 2>;
	using mat3f = mat<sk_float, 3, 3>;
	using mat4f = mat<sk_float, 4, 4>;

	using mat2 = mat2f;
	using mat3 = mat3f;
	using mat4 = mat4f;

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