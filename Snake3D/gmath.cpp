#include "gmath.h"
#include <cmath>
#include <algorithm>
#include <stdexcept>

namespace gmt 
{
	vec2f::vec2f(GLfloat x_, GLfloat y_)
	{
		x = x_;
		y = y_;
	}

	vec2f::vec2f(const vec2f& p1, const vec2f& p2)
	{
		x = p2.x - p1.x;
		y = p2.y - p1.y;
	}

	vec2f vec2f::operator+(const vec2f& o) const
	{
		return vec2(x + o.x, y + o.y);
	}

	vec2f vec2f::operator*(GLfloat k) const
	{
		return vec2f(x * k, y * k);
	}

	vec2f vec2f::operator/(GLfloat k) const
	{
		if (k == GLF_ZERO)
			throw std::runtime_error("Division by zero");

		return vec2f(x / k, y / k);
	}

	vec2f& vec2f::operator+=(const vec2f& o)
	{
		return *this = *this + o;
	}

	vec2f& vec2f::operator*=(GLfloat k)
	{
		return *this = *this * k;
	}

	vec2f& vec2f::operator/=(GLfloat k)
	{
		return *this = *this / k;
	}

	bool vec2f::operator==(const vec2f& o)
	{
		return x == o.x && y == o.y;
	}

	vec3f::vec3f(GLfloat x_, GLfloat y_, GLfloat z_)
	{
		x = x_;
		y = y_;
		z = z_;
	}

	vec3f::vec3f(const vec3f& p1, const vec3f& p2)
	{
		x = p2.x - p1.x;
		y = p2.y - p1.y;
		z = p2.y - p1.y;
	}

	vec3f::vec3f(GLfloat val)
	{
		x = val;
		y = val;
		z = val;
	}

	vec3f vec3f::operator+(const vec3f& o) const
	{
		return vec3f(x + o.x, y + o.y, z + o.z);
	}

	vec3f vec3f::operator-(const vec3f& o) const
	{
		return (*this) + (-o);
	}

	vec3f vec3f::operator-() const
	{
		return { -x, -y, -z };
	}

	vec3f vec3f::operator*(GLfloat k) const
	{
		return vec3f(x * k, y * k, z * k);
	}

	vec3f vec3f::operator/(GLfloat k) const
	{
		return (*this) * (1.0f / k);
	}

	vec3f& vec3f::operator+=(const vec3f& o)
	{
		return (*this) = (*this) + o;
	}

	vec3f& vec3f::operator-=(const vec3f& o)
	{
		return (*this) = (*this) - o;
	}

	bool vec3f::operator==(const vec3f& o) const
	{
		return x == o.x && y == o.y && z == o.z;
	}

	bool vec3f::operator!=(const vec3f& o) const
	{
		return !(*this == o);
	}

	bool vec3f::operator<(const vec3f& o) const
	{
		if (x != o.x)
			return x < o.x;

		if (y != o.y)
			return y < o.z;

		return z < o.z;
	}

	bool vec3f::operator>(const vec3f& o) const
	{
		if (x != o.x)
			return x > o.x;

		if (y != o.y)
			return y > o.z;

		return z > o.z;
	}

	vec4f::vec4f(GLfloat x_, GLfloat y_, GLfloat z_, GLfloat w_)
	{
		x = x_;
		y = y_;
		z = z_;
		w = w_;
	}

	bool vec3i::operator<(const vec3i& o) const
	{
		if (x != o.x)
			return x < o.x;

		if (y != o.y)
			return y < o.y;

		return z < o.z;
	}

	bool vec3i::operator==(const vec3i& o) const
	{
		return x == o.x && y == o.y && z == o.z;
	}

	bool vec3i::operator!=(const vec3i& o) const
	{
		return x != o.x || y != o.y || z != o.z;
	}

	GLfloat dot(const vec2f& v1, const vec2f& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	GLfloat dot(const vec3f& v1, const vec3f& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	GLfloat cross(const vec2f& v1, const vec2f& v2)
	{
		return v1.x * v2.y - v1.y * v2.x;
	}

	GLfloat cross(const vec3f& v1, const vec3f& v2)
	{
		vec3f cv = crossVector(v1, v2);

		return dot(cv, normalize(cv));
	}

	vec3f crossVector(const vec3f& v1, const vec3f& v2)
	{
		return { v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x };
	}

	GLfloat distance(const vec2f& p1, const vec2f& p2)
	{
		return std::sqrt(sqr(p1.x - p2.x) + sqr(p1.y - p2.y));
	}

	GLfloat distance(const vec3f& p1, const vec3f& p2)
	{
		return std::sqrt(sqr(p1.x - p2.x) + sqr(p1.y - p2.y) + sqr(p1.z - p2.z));
	}

	GLfloat length(const vec2f& v)
	{
		return std::sqrt(v.x * v.x + v.y * v.y);
	}

	GLfloat length(const vec3f& v)
	{
		return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	}

	vec2f normalize(const vec2f& v)
	{
		GLfloat len = length(v);

		return len == GLF_ZERO ? v : v / len;
	}

	vec3f normalize(const vec3f& v)
	{
		GLfloat len = length(v);

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

	GLfloat sqr(GLfloat x)
	{
		return x * x;
	}

	std::ostream& operator<<(std::ostream& o, const vec2& v)
	{
		o << v.x << " " << v.y << std::endl;

		return o;
	}

	vec2 operator*(const mat2& m, const vec2& v)
	{
		auto res = m * mat<GLfloat, 2, 1>({ {v.x}, {v.y} });

		return vec2(res[0][0], res[1][0]);
	}

	vec3 operator*(const mat3& m, const vec3& v)
	{
		auto res = m * mat<GLfloat, 3, 1>({ {v.x}, {v.y}, {v.z} });

		return vec3(res[0][0], res[1][0], res[2][0]);
	}

	vec4 operator*(const mat4& m, const vec4& v)
	{
		auto res = m * mat<GLfloat, 4, 1>({ {v.x}, {v.y}, {v.z}, {v.w} });

		return vec4(res[0][0], res[1][0], res[2][0], res[3][0]);
	}

	mat4 translate(const vec3& v)
	{
		return mat4({ {1.0f, 0.0f, 0.0f, v.x}, 
					  {0.0f, 1.0f, 0.0f, v.y},
					  {0.0f, 0.0f, 1.0f, v.z},
					  {0.0f, 0.0f, 0.0f, 1.0f} });
	}

	mat4 rotateX(GLfloat angle)
	{
		return mat4({ { 1.0f, 0.0f, 0.0f, 0.0f},
					  { 0.0f, cos(angle), -sin(angle), 0.0f},
					  { 0.0f, sin(angle),  cos(angle), 0.0f},
					  { 0.0f,       0.0f,       0.0f, 1.0f} });
	}

	mat4 rotateY(GLfloat angle)
	{
		return mat4({ { cos(angle), 0.0f, sin(angle), 0.0f},
					  { 0.0f, 1.0f, 0.0f, 0.0f},
					  { -sin(angle), 0.0f, cos(angle), 0.0f},
					  { 0.0f, 0.0f, 0.0f, 1.0f} });
	}

	mat4 rotateZ(GLfloat angle)
	{
		return mat4({ { cos(angle), -sin(angle), 0.0f, 0.0f},
					  { sin(angle), cos(angle), 0.0f, 0.0f},
					  { 0.0f,       0.0f,       1.0f, 0.0f},
					  { 0.0f,       0.0f,       0.0f, 1.0f} });
	}

	mat4 rotate(GLfloat angle, const vec3& v)
	{
		if (angle == GLF_ZERO)
			return mat4(1.0f);

		if (v.x == GLF_ZERO && v.z == GLF_ZERO)
			return rotateY(angle);

		vec3 p = { v.x, 0.0f, v.z };
		vec3 g = { 0.0f, 0.0f, 1.0f };

		const GLfloat beta = calcAngle(p, g);
		const GLfloat theta = calcAngle(v, p);

		mat4 res(1.0f);

		res *= rotateY(beta);
		res *= rotateX(-theta);
		res *= rotateZ(angle);
		res *= rotateX(theta);
		res *= rotateY(-beta);

		return res;
	}

	mat4 scale(GLfloat scaler)
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

	mat4 perspective(GLfloat fov, GLfloat widthToHeightRatio, GLfloat nearPlane, GLfloat farPlane)
	{
		GLfloat k = widthToHeightRatio;
		GLfloat tg = std::tan(fov * 0.5f);

		GLfloat gdiv = std::sqrt(1.0f - sqr(k) * sqr(tg));

		if(gdiv == GLF_ZERO)
			throw std::runtime_error("division by zero");

		GLfloat g = (2.0f * tg) / gdiv;
		GLfloat e = nearPlane;
		GLfloat f = farPlane;

		if (e == f || g == GLF_ZERO || k == GLF_ZERO || e == GLF_ZERO)
			throw std::runtime_error("division by zero");
		
		return mat4({ {2.0f / (g * k), 0.0f    , 0.0f               , 0.0f                       },
					  {0.0f          , 2.0f / g, 0.0f               , 0.0f                       },
					  {0.0f          , 0.0f    , (e + f) / (e - f)  , (2.0f * e * f) / (e - f)	 },
					  {0.0f          , 0.0f    , -1.0f              , 0.0f                       } });
	}

	mat4 ortho(float_t minX, float_t maxX, float_t minY, float_t maxY)
	{
		float_t dx = (maxX - minX);
		float_t dy = (maxY - minY);
		float_t xmul = 1.0f / dx;
		float_t ymul = 1.0f / dy;

		return mat4({ {2.0f * xmul, 0.0f, 0.0f, -minX * xmul * 2.0f - 1.0f},
					  {0.0f, 2.0f * ymul, 0.0f, -minY * ymul * 2.0f - 1.0f},
					  {0.0f, 0.0f, 1.0f, 0.0f},
					  {0.0f, 0.0f, 0.0f, 1.0f} });
	}

	GLfloat radians(GLfloat degrees)
	{
		return degrees * PI / 180.0f;
	}

	GLfloat cutAngle(GLfloat angle)
	{
		if (angle < GLF_ZERO)
			angle += 2.0f * PI;

		if (angle > 2.0f * PI)
			angle -= 2.0f * PI;

		return angle;
	}

	GLfloat calcAngle(vec3 v1, vec3 v2)
	{
		v1 = normalize(v1);
		v2 = normalize(v2);

		GLfloat dt = dot(v1, v2);
		GLfloat crs = cross(v1, v2);

		if (crs == GLF_ZERO)
			return GLF_ZERO;

		return std::atan2(crs, dt);
	}
}