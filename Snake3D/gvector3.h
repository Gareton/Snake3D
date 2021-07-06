#ifndef GVECTOR3_H
#define GVECTOR3_H
#include "gvector2.h"

namespace gmt 
{
	template<typename T>
	struct vec3_impl
	{
		vec3_impl() = default;
		vec3_impl(const vec3_impl& o) = default;
		vec3_impl& operator=(const vec3_impl& o) = default;
		explicit vec3_impl(const T& val);
		vec3_impl(const T& x_, const T& y_, const T& z_);
		vec3_impl(const T& x_, const vec2_impl<T>& yz);
		vec3_impl(const vec2_impl<T>& xy, const T& z_);
		vec3_impl(const vec3_impl& p1, const vec3_impl& p2); 

		template<typename Q>
		explicit vec3_impl(const vec3_impl<Q>& o);

		vec3_impl operator-() const;
		vec3_impl operator+(const vec3_impl& o) const;
		vec3_impl operator-(const vec3_impl& o) const;
		vec3_impl operator*(const vec3_impl& o) const;
		vec3_impl operator*(const T& val) const;
		vec3_impl operator/(const T& val) const;

		vec3_impl& operator+=(const vec3_impl& o);
		vec3_impl& operator-=(const vec3_impl& o);
		vec3_impl& operator*=(const vec3_impl& o);
		vec3_impl& operator*=(const T& val);
		vec3_impl& operator/=(const T& val);

		bool operator==(const vec3_impl& o) const;
		bool operator!=(const vec3_impl& o) const;
		bool operator<(const vec3_impl& o) const;
		bool operator>(const vec3_impl& o) const;

		T x, y, z;
	};


	template<typename T>
	vec3_impl<T>::vec3_impl(const T& val)
		: x(val), y(val), z(val) {}

	template<typename T>
	vec3_impl<T>::vec3_impl(const T& x_, const T& y_, const T& z_)
		: x(x_), y(y_), z(z_) {}

	template<typename T>
	vec3_impl<T>::vec3_impl(const T& x_, const vec2_impl<T>& yz)
		: x(x_), y(yz.x), z(yz.y) {}

	template<typename T>
	vec3_impl<T>::vec3_impl(const vec2_impl<T>& xy, const T& z_)
		: x(xy.x), y(xy.y), z(z_) {}

	template<typename T>
	vec3_impl<T>::vec3_impl(const vec3_impl& p1, const vec3_impl& p2)
		: x(p2.x - p1.x), y(p2.y - p1.y), z(p2.z - p1.z) {}

	template<typename T>
	template<typename Q>
	vec3_impl<T>::vec3_impl(const vec3_impl<Q>& o)
		: x(T(o.x)), y(T(o.y)), z(T(o.z)) {}

	template<typename T>
	vec3_impl<T> vec3_impl<T>::operator-() const
	{
		return {-x, -y, -z};
	}

	template<typename T>
	vec3_impl<T> vec3_impl<T>::operator+(const vec3_impl& o) const
	{
		return {x + o.x, y + o.y, z + o.z};
	}

	template<typename T>
	vec3_impl<T> vec3_impl<T>::operator-(const vec3_impl& o) const
	{
		return {x - o.x, y - o.y, z - o.z};
	}

	template<typename T>
	vec3_impl<T> vec3_impl<T>::operator*(const vec3_impl& o) const
	{
		return { x * o.x, y * o.y, z * o.z };
	}

	template<typename T>
	vec3_impl<T> vec3_impl<T>::operator*(const T& val) const
	{
		return {x * val, y * val, z * val};
	}

	template<typename T>
	vec3_impl<T> vec3_impl<T>::operator/(const T& val) const
	{
		return {x / val, y / val, z / val};
	}

	template<typename T>
	vec3_impl<T>& vec3_impl<T>::operator+=(const vec3_impl& o)
	{
		return *this = (*this) + o;
	}

	template<typename T>
	vec3_impl<T>& vec3_impl<T>::operator-=(const vec3_impl& o)
	{
		return *this = (*this) - o;
	}

	template<typename T>
	vec3_impl<T>& vec3_impl<T>::operator*=(const vec3_impl& o)
	{
		return *this = (*this) * o;
	}

	template<typename T>
	vec3_impl<T>& vec3_impl<T>::operator*=(const T& val)
	{
		return *this = (*this) * val;
	}

	template<typename T>
	vec3_impl<T>& vec3_impl<T>::operator/=(const T& val)
	{
		return *this = (*this) / val;
	}

	template<typename T>
	bool vec3_impl<T>::operator==(const vec3_impl& o) const
	{
		return x == o.x && y == o.y && z == o.z;
	}

	template<typename T>
	bool vec3_impl<T>::operator!=(const vec3_impl& o) const
	{
		return x != o.x || y != o.y || z != o.z;
	}

	template<typename T>
	bool vec3_impl<T>::operator<(const vec3_impl& o) const
	{
		if (x != o.x)
			return x < o.x;

		if (y != o.y)
			return y < o.y;

		return z < o.z;
	}

	template<typename T>
	bool vec3_impl<T>::operator>(const vec3_impl& o) const
	{
		if (x != o.x)
			return x > o.x;

		if (y != o.y)
			return y > o.y;

		return z > o.z;
	}

}

#endif
