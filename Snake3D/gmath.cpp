#include "gmath.h"
#include <cmath>
#include <algorithm>
#include <stdexcept>

namespace gmt 
{
	sk_float dot(const vec2f& v1, const vec2f& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	sk_float dot(const vec3f& v1, const vec3f& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	sk_float cross(const vec2f& v1, const vec2f& v2)
	{
		return v1.x * v2.y - v1.y * v2.x;
	}

	sk_float cross(const vec3f& v1, const vec3f& v2)
	{
		vec3f cv = crossVector(v1, v2);

		return dot(cv, normalize(cv));
	}

	vec3f crossVector(const vec3f& v1, const vec3f& v2)
	{
		return { v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x };
	}

	sk_float distance(const vec2f& p1, const vec2f& p2)
	{
		return std::sqrt(sqr(p1.x - p2.x) + sqr(p1.y - p2.y));
	}

	sk_float distance(const vec3f& p1, const vec3f& p2)
	{
		return std::sqrt(sqr(p1.x - p2.x) + sqr(p1.y - p2.y) + sqr(p1.z - p2.z));
	}

	sk_float length(const vec2f& v)
	{
		return std::sqrt(v.x * v.x + v.y * v.y);
	}

	sk_float length(const vec3f& v)
	{
		return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	}

	vec2f normalize(const vec2f& v)
	{
		sk_float len = length(v);

		return len == GLF_ZERO ? v : v / len;
	}

	vec3f normalize(const vec3f& v)
	{
		sk_float len = length(v);

		return len == GLF_ZERO ? v : v / len;
	}

	vec2f getNormal(const vec2f& p1, const vec2f& p2)
	{
		vec2f v = normalize(vec2f(p1, p2));

		std::swap(v.x, v.y);
		v.x *= -1.0f;

		return v;
	}

	vec2f getMiddle(const vec2f& p1, const vec2f& p2)
	{
		vec2f v = normalize(gmt::vec2f(p1, p2));

		v *= gmt::distance(p1, p2) / 2.0f;

		return p1 + v;
	}

	sk_float sqr(sk_float x)
	{
		return x * x;
	}

	std::ostream& operator<<(std::ostream& o, const vec2f& v)
	{
		o << v.x << " " << v.y << std::endl;

		return o;
	}

	vec2f operator*(const mat2& m, const vec2f& v)
	{
		auto res = m * mat<sk_float, 2, 1>({ {v.x}, {v.y} });

		return vec2f(res[0][0], res[1][0]);
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

	mat4 translate(const vec3& v)
	{
		return mat4({ {1.0f, 0.0f, 0.0f, v.x}, 
					  {0.0f, 1.0f, 0.0f, v.y},
					  {0.0f, 0.0f, 1.0f, v.z},
					  {0.0f, 0.0f, 0.0f, 1.0f} });
	}

	mat4 rotateX(sk_float angle)
	{
		return mat4({ { 1.0f, 0.0f, 0.0f, 0.0f},
					  { 0.0f, cos(angle), -sin(angle), 0.0f},
					  { 0.0f, sin(angle),  cos(angle), 0.0f},
					  { 0.0f,       0.0f,       0.0f, 1.0f} });
	}

	mat4 rotateY(sk_float angle)
	{
		return mat4({ { cos(angle), 0.0f, sin(angle), 0.0f},
					  { 0.0f, 1.0f, 0.0f, 0.0f},
					  { -sin(angle), 0.0f, cos(angle), 0.0f},
					  { 0.0f, 0.0f, 0.0f, 1.0f} });
	}

	mat4 rotateZ(sk_float angle)
	{
		return mat4({ { cos(angle), -sin(angle), 0.0f, 0.0f},
					  { sin(angle), cos(angle), 0.0f, 0.0f},
					  { 0.0f,       0.0f,       1.0f, 0.0f},
					  { 0.0f,       0.0f,       0.0f, 1.0f} });
	}

	mat4 rotate(sk_float angle, const vec3& v)
	{
		if (angle == GLF_ZERO)
			return mat4(1.0f);

		if (v.x == GLF_ZERO && v.z == GLF_ZERO)
			return rotateY(angle);

		vec3 p = { v.x, 0.0f, v.z };
		vec3 g = { 0.0f, 0.0f, 1.0f };

		const sk_float beta = calcAngle(p, g);
		const sk_float theta = calcAngle(v, p);

		mat4 res(1.0f);

		res *= rotateY(beta);
		res *= rotateX(-theta);
		res *= rotateZ(angle);
		res *= rotateX(theta);
		res *= rotateY(-beta);

		return res;
	}

	mat4 scale(sk_float scaler)
	{
		return mat4({ {scaler, 0.0f,   0.0f, 0.0f},
					  {0.0f,   scaler, 0.0f, 0.0f},
					  {0.0f,   0.0f,   scaler, 0.0f},
					  {0.0f,   0.0f,   0.0f, 1.0f} });
	}

	mat4 scale(const vec3& v)
	{
		return mat4({ {v.x, 0.0f,   0.0f, 0.0f},
					  {0.0f,   v.y, 0.0f, 0.0f},
					  {0.0f,   0.0f,   v.z, 0.0f},
				      {0.0f,   0.0f,   0.0f, 1.0f} });
	}

	mat4 perspective(sk_float fov, sk_float widthToHeightRatio, sk_float nearPlane, sk_float farPlane)
	{
		sk_float k = widthToHeightRatio;
		sk_float tg = std::tan(fov * 0.5f);

		sk_float gdiv = std::sqrt(1.0f - sqr(k) * sqr(tg));

		if(gdiv == GLF_ZERO)
			throw std::runtime_error("division by zero");

		sk_float g = (2.0f * tg) / gdiv;
		sk_float e = nearPlane;
		sk_float f = farPlane;

		if (e == f || g == GLF_ZERO || k == GLF_ZERO || e == GLF_ZERO)
			throw std::runtime_error("division by zero");
		
		return mat4({ {2.0f / (g * k), 0.0f    , 0.0f               , 0.0f                       },
					  {0.0f          , 2.0f / g, 0.0f               , 0.0f                       },
					  {0.0f          , 0.0f    , (e + f) / (e - f)  , (2.0f * e * f) / (e - f)	 },
					  {0.0f          , 0.0f    , -1.0f              , 0.0f                       } });
	}

	mat4 ortho(sk_float minX, sk_float maxX, sk_float minY, sk_float maxY)
	{
		sk_float dx = (maxX - minX);
		sk_float dy = (maxY - minY);
		sk_float xmul = 1.0f / dx;
		sk_float ymul = 1.0f / dy;

		return mat4({ {2.0f * xmul, 0.0f, 0.0f, -minX * xmul * 2.0f - 1.0f},
					  {0.0f, 2.0f * ymul, 0.0f, -minY * ymul * 2.0f - 1.0f},
					  {0.0f, 0.0f, 1.0f, 0.0f},
					  {0.0f, 0.0f, 0.0f, 1.0f} });
	}

	sk_float radians(sk_float degrees)
	{
		return degrees * PI / 180.0f;
	}

	sk_float cutAngle(sk_float angle)
	{
		if (angle < GLF_ZERO)
			angle += 2.0f * PI;

		if (angle > 2.0f * PI)
			angle -= 2.0f * PI;

		return angle;
	}

	sk_float calcAngle(vec3 v1, vec3 v2)
	{
		v1 = normalize(v1);
		v2 = normalize(v2);

		sk_float dt = dot(v1, v2);
		sk_float crs = cross(v1, v2);

		if (crs == GLF_ZERO)
			return GLF_ZERO;

		return std::atan2(crs, dt);
	}

	sk_uint randomUint()
	{
		static std::mt19937 rnd(std::chrono::high_resolution_clock::now().time_since_epoch().count());

		return rnd();
	}
}