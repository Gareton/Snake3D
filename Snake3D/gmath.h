#ifndef GMATH_H
#define GMATH_H
#include <glad/glad.h>
#include <array>
#include <initializer_list>
#include <iostream>

namespace gmt
{
	const GLfloat GLF_ZERO = static_cast<GLfloat>(0);
	const GLfloat PI = static_cast<GLfloat>(acos(-1.0f));

	struct vec2f
	{
		vec2f() = default;
		vec2f(GLfloat x_, GLfloat y_);
		vec2f(const vec2f &p1, const vec2f &p2);

		vec2f operator+(const vec2f& o) const;
		vec2f operator*(GLfloat k) const;
		vec2f operator/(GLfloat k) const;
		vec2f& operator+=(const vec2f& o);
		vec2f& operator*=(GLfloat k);
		vec2f& operator/=(GLfloat k);
		bool operator==(const vec2f& o); 

		GLfloat x, y;
	};

	struct vec3f
	{
		vec3f() = default;
		vec3f(GLfloat x_, GLfloat y_, GLfloat z_);
		vec3f(const vec3f& p1, const vec3f& p2);
		explicit vec3f(GLfloat val);

		vec3f operator+(const vec3f& o) const;
		vec3f operator-(const vec3f& o) const;
		vec3f operator-() const;
		vec3f operator*(GLfloat k) const;
		vec3f operator/(GLfloat k) const;
		vec3f& operator+=(const vec3f& o);
		vec3f& operator-=(const vec3f& o);
		vec3f& operator*=(GLfloat k);
		vec3f& operator/=(GLfloat k);
		bool operator==(const vec3f& o) const;
		bool operator!=(const vec3f& o) const;
		bool operator<(const vec3f& o) const;
		bool operator>(const vec3f& o) const;

		GLfloat x, y, z;
	};

	struct vec4f
	{
		vec4f() = default;
		vec4f(GLfloat x_, GLfloat y_, GLfloat z_, GLfloat w_);
		vec4f(const vec4f& p1, const vec4f& p2);

		vec4f operator+(const vec4f& o) const;
		vec4f operator*(GLfloat k) const;
		vec4f operator/(GLfloat k) const;
		vec4f& operator+=(const vec4f& o);
		vec4f& operator*=(GLfloat k);
		vec4f& operator/=(GLfloat k);
		bool operator==(const vec4f& o);

		GLfloat x, y, z, w;
	};

	struct vec3i
	{
		vec3i() = default;
		vec3i(int32_t x_, int32_t y_, int32_t z_)
		{
			x = x_;
			y = y_;
			z = z_;
		}

		bool operator<(const vec3i& o) const;
		bool operator==(const vec3i& o) const;
		bool operator!=(const vec3i& o) const;

		int32_t x, y, z;
	};

	struct vec2i
	{
		vec2i() = default;
		vec2i(int32_t x_, int32_t y_)
		{
			x = x_;
			y = y_;
		}

		int32_t x, y;
	};

	GLfloat dot(const vec2f& v1, const vec2f& v2);
	GLfloat dot(const vec3f& v1, const vec3f& v2);

	GLfloat cross(const vec2f& v1, const vec2f& v2);
	GLfloat cross(const vec2f& v1, const vec2f& v2);

	vec3f crossVector(const vec3f& v1, const vec3f& v2);

	GLfloat distance(const vec2f& p1, const vec2f& p2);
	GLfloat distance(const vec3f& p1, const vec3f& p2);

	GLfloat length(const vec2f& v);
	GLfloat length(const vec3f& v);

	vec2f normalize(const vec2f& v);
	vec3f normalize(const vec3f& v);

	vec2f getNormal(const vec2f& p1, const vec2f& p2);
	vec3f getNormal(const vec3f& p1, const vec3f& p2);

	vec2f getMiddle(const vec2f& p1, const vec2f& p2);
	vec3f getMiddle(const vec3f& p1, const vec3f& p2);

	GLfloat sqr(GLfloat x);

	using vec2 = vec2f;
	using vec3 = vec3f;
	using vec4 = vec4f;

	template<typename T, size_t N, size_t M>
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

			for (size_t i = 0; i < N; ++i)
				for (size_t j = 0; j < M; ++j)
					_data[i][j] = o._data[i][j];

			return *this;
		}

		mat operator+(const mat& o) const
		{
			mat rval;

			for (size_t i = 0; i < N; ++i)
				for (size_t j = 0; j < M; ++j)
					rval[i][j] = _data[i][j] + o._data[i][j];

			return std::move(rval);
		}

		mat operator-() const
		{
			mat rval;

			for (size_t i = 0; i < N; ++i)
				for (size_t j = 0; j < M; ++j)
					rval[i][j] = -_data[i][j];

			return std::move(rval);
		}

		mat operator-(const mat& o) const
		{
			return std::move(*this + (-o));
		}

		template<size_t Q>
		mat<T, N, Q> operator*(const mat<T, M, Q>& o) const
		{
			mat<T, N, Q> rval;

			for (size_t i = 0; i < N; ++i)
				for (size_t j = 0; j < Q; ++j)
					for (size_t k = 0; k < M; ++k)
						rval[i][j] += _data[i][k] * o.get(k, j);
			
			return std::move(rval);
		}

		template<size_t Q>
		mat<T, N, Q>& operator*=(const mat<T, M, Q>& o)
		{
			return (*this) = (*this) * o;
		}

		T* operator[](size_t row) 
		{
			if (row >= N)
				throw std::runtime_error("gmath.h::mat::operator[]::index_out_of_bounds");

			return _data[row];
		}

		const T& get(size_t row, size_t col) const
		{
			if (row >= N || col >= M)
				throw std::runtime_error("gmath.h::mat::get::index_out_of_bounds");

			return _data[row][col];
		}

	private:
		T _data[N][M] = {};
	};

	using mat2f = mat<GLfloat, 2, 2>;
	using mat3f = mat<GLfloat, 3, 3>;
	using mat4f = mat<GLfloat, 4, 4>;

	using mat2 = mat2f;
	using mat3 = mat3f;
	using mat4 = mat4f;

	template<typename T, size_t N, size_t M>
	std::ostream& operator<<(std::ostream& o, const mat<T, N, M>& m)
	{
		for (size_t i = 0; i < N; ++i)
		{
			for (size_t j = 0; j < M; ++j)
				o << m.get(i, j) << " ";

			if (i + 1 != N)
				o << std::endl;
		}

		return o;
	}

	std::ostream& operator<<(std::ostream& o, const vec2& v);
	std::ostream& operator<<(std::ostream& o, const vec3& v);
	std::ostream& operator<<(std::ostream& o, const vec4& v);

	vec2 operator*(const mat2& m, const vec2& v);
	vec3 operator*(const mat3& m, const vec3& v);
	vec4 operator*(const mat4& m, const vec4& v);

	mat4 translate(const vec3& v);
	mat4 rotateX(GLfloat angle);
	mat4 rotateY(GLfloat angle);
	mat4 rotateZ(GLfloat angle);
	mat4 rotate(GLfloat angle, const vec3& v);
	mat4 scale(GLfloat scaler);
	mat4 scale(const vec3& v);
	mat4 perspective(GLfloat fov, GLfloat widthToHeightRatio, GLfloat nearPlane, GLfloat farPlane);
	mat4 ortho(float_t minX, float_t maxX, float_t minY, float_t maxY);

	GLfloat radians(GLfloat degrees);
	GLfloat cutAngle(GLfloat angle);
	GLfloat calcAngle(vec3 v1, vec3 v2);

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
}

#endif