#ifndef GVECTOR4_H
#define GVECTOR4_H
#include "gvector3.h"

namespace gmt
{
	template<typename T>
	struct vec4_impl
	{
		vec4_impl() = default;
		vec4_impl(const vec4_impl& o) = default;
		vec4_impl& operator=(const vec4_impl& o) = default;
		explicit vec4_impl(const T& val);
		vec4_impl(const T& x_, const T& y_, const T& z_, const T& w_);
		vec4_impl(const T& x_, const T& y_, const vec2_impl<T>& zw);
		vec4_impl(const vec2_impl<T>& xy, const T& z_, const T& w_);
		vec4_impl(const T& x_, const vec3_impl<T>& yzw);
		vec4_impl(const vec3_impl<T>& xyz, const T& w_);
		vec4_impl(const vec4_impl& p1, const vec4_impl& p2); 

		template<typename Q>
		explicit vec4_impl(const vec4_impl<Q>& o);

		vec4_impl operator-() const;
		vec4_impl operator+(const vec4_impl& o) const;
		vec4_impl operator-(const vec4_impl& o) const;
		vec4_impl operator*(const T& val) const;
		vec4_impl operator/(const T& val) const;

		vec4_impl& operator+=(const vec4_impl& o);
		vec4_impl& operator-=(const vec4_impl& o);
		vec4_impl& operator*=(const T& val);
		vec4_impl& operator/=(const T& val);

		bool operator==(const vec4_impl& o) const;
		bool operator!=(const vec4_impl& o) const;
		bool operator<(const vec4_impl& o) const;
		bool operator>(const vec4_impl& o) const;

		T x, y, z, w;
	};

	template<typename T>
	vec4_impl<T>::vec4_impl(const T& val)
		: x(val), y(val), z(val), w(val) {}

	template<typename T>
	vec4_impl<T>::vec4_impl(const T& x_, const T& y_, const T& z_, const T& w_)
		: x(x_), y(y_), z(z_), w(w_) {}

	template<typename T>
	vec4_impl<T>::vec4_impl(const T& x_, const T& y_, const vec2_impl<T>& zw)
		: x(x_), y(y_), z(zw.x), w(zw.y) {}

	template<typename T>
	vec4_impl<T>::vec4_impl(const vec2_impl<T>& xy, const T& z_, const T& w_)
		: x(xy.x), y(xy.y), z(z_), w(w_) {}

	template<typename T>
	vec4_impl<T>::vec4_impl(const T& x_, const vec3_impl<T>& yzw)
		: x(x_), y(yzw.x), z(yzw.y), w(yzw.z) {}

	template<typename T>
	vec4_impl<T>::vec4_impl(const vec3_impl<T>& xyz, const T& w_)
		: x(xyz.x), y(xyz.y), w(xyz.z), w(w_) {}

	template<typename T>
	vec4_impl<T>::vec4_impl(const vec4_impl& p1, const vec4_impl& p2)
		: x(p2.x - p1.x), y(p2.y - p1.y), z(p2.z - p1.z), w(p2.w - p1.w) {}

	template<typename T>
	template<typename Q>
	vec4_impl<T>::vec4_impl(const vec4_impl<Q>& o)
		: x(T(o.x)), y(T(o.y)), z(T(o.z)), w(T(o.w)) {}

	template<typename T>
	vec4_impl<T> vec4_impl<T>::operator-() const
	{
		return {-x, -y, -z, -w};
	}

	template<typename T>
	vec4_impl<T> vec4_impl<T>::operator+(const vec4_impl& o) const
	{
		return {x + o.x, y + o.y, z + o.z, w + o.w};
	}

	template<typename T>
	vec4_impl<T> vec4_impl<T>::operator-(const vec4_impl& o) const
	{
		return {x - o.x, y - o.y, z - o.z, w - o.w};
	}

	template<typename T>
	vec4_impl<T> vec4_impl<T>::operator*(const T& val) const
	{
		return {x * val, y * val, z * val, w * val};
	}

	template<typename T>
	vec4_impl<T> vec4_impl<T>::operator/(const T& val) const
	{
		return {x / val, y / val, z / val, w / val};
	}

	template<typename T>
	vec4_impl<T>& vec4_impl<T>::operator+=(const vec4_impl& o)
	{
		return *this = (*this) + o;
	}

	template<typename T>
	vec4_impl<T>& vec4_impl<T>::operator-=(const vec4_impl& o)
	{
		return *this = (*this) - o;
	}

	template<typename T>
	vec4_impl<T>& vec4_impl<T>::operator*=(const T& val)
	{
		return *this = (*this) * val;
	}

	template<typename T>
	vec4_impl<T>& vec4_impl<T>::operator/=(const T& val)
	{
		return *this = (*this) / val;
	}

	template<typename T>
	bool vec4_impl<T>::operator==(const vec4_impl& o) const
	{
		return x == o.x && y == o.y && z == o.z, w == o.w;
	}

	template<typename T>
	bool vec4_impl<T>::operator!=(const vec4_impl& o) const
	{
		return x != o.x || y != o.y || z != o.z || w != o.w;
	}

	template<typename T>
	bool vec4_impl<T>::operator<(const vec4_impl& o) const
	{
		if (x != o.x)
			return x < o.x;

		if (y != o.y)
			return y < o.y;

		if (z != o.z)
			return z < o.z;

		return w < o.w;
	}

	template<typename T>
	bool vec4_impl<T>::operator>(const vec4_impl& o) const
	{
		if (x != o.x)
			return x > o.x;

		if (y != o.y)
			return y > o.y;

		if (z != o.z)
			return z > o.z;

		return w > o.w;
	}
}

#endif
