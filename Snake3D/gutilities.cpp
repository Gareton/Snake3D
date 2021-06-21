#include "gutilities.h"
#include <cmath>
#include <stdexcept>
#include <random>
#include <chrono>

namespace gmt
{
	sk_uint random()
	{
		static std::mt19937 generator(std::chrono::high_resolution_clock::now().time_since_epoch().count());

		return generator();
	}

	sk_float sqrt(sk_float val)
	{
		return std::sqrt(val);
	}

	sk_float radians(sk_float degrees)
	{
		return degrees * PI / 180.0f;
	}

	sk_float fmod(sk_float val, sk_float m)
	{
		if (m <= GLF_ZERO)
			throw std::runtime_error("gmath::fmod::module_must_be_greater_than_zero");
		
		sk_int signedCount = truncf(val / m);

		val -= signedCount * m;

		if (val < GLF_ZERO)
			val += m;
		else if (val >= m)
			val -= m;

		return val;
	}

	sk_float cut(sk_float angle)
	{
		return fmod(angle, PI * 2.0f);
	}

	vec2 operator*(const mat2& m, const vec2& v)
	{
		auto res = m * mat<sk_float, 2, 1>({ {v.x}, {v.y} });

		return vec2(res[0][0], res[1][0]);
	}

	vec3 operator*(const mat3& m, const vec3& v)
	{
		auto res = m * mat<sk_float, 3, 1>({ {v.x}, {v.y}, {v.z} });

		return vec3(res[0][0], res[1][0], res[2][0]);
	}

	vec4 operator*(const mat4& m, const vec4& v)
	{
		auto res = m * mat<sk_float, 4, 1>({ {v.x}, {v.y}, {v.z}, {v.w} });

		return vec4(res[0][0], res[1][0], res[2][0], res[3][0]);
	}

	sk_float sin(sk_float angle)
	{
		return std::sin(angle);
	}

	sk_float cos(sk_float angle)
	{
		return std::cos(angle);
	}

	sk_float tan(sk_float angle)
	{
		return std::tan(angle);
	}

	sk_float asin(sk_float angle)
	{
		return std::asin(angle);
	}

	sk_float acos(sk_float angle)
	{
		return std::acos(angle);
	}

	sk_float ctan(sk_float angle)
	{
		return 1.0f / tan(angle);
	}

	sk_float atan2(sk_float y, sk_float x)
	{
		return std::atan2(y, x);
	}
}