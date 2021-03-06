#ifndef GVECTOR2_H
#define GVECTOR2_H

namespace gmt
{
	template<typename T>
	struct vec2_impl
	{
		vec2_impl() = default;
		vec2_impl(const vec2_impl& o) = default;
		vec2_impl& operator=(const vec2_impl& o) = default;
		explicit vec2_impl(const T& val);
		vec2_impl(const T& x_, const T& y_);
		vec2_impl(const vec2_impl& p1, const vec2_impl& p2);

		template<typename Q>
		explicit vec2_impl(const vec2_impl<Q>& o);

		vec2_impl operator-() const;
		vec2_impl operator+(const vec2_impl& o) const;
		vec2_impl operator-(const vec2_impl& o) const;
		vec2_impl operator*(const T& val) const;
		vec2_impl operator/(const T& val) const;

		vec2_impl& operator+=(const vec2_impl& o);
		vec2_impl& operator-=(const vec2_impl& o);
		vec2_impl& operator*=(const T& val);
		vec2_impl& operator/=(const T& val);

		bool operator==(const vec2_impl& o) const;
		bool operator!=(const vec2_impl& o) const;
		bool operator<(const vec2_impl& o) const;
		bool operator>(const vec2_impl& o) const;

		T x, y;
	};

	template<typename T>
	vec2_impl<T>::vec2_impl(const T& val)
		: x(val), y(val) {}

	template<typename T>
	vec2_impl<T>::vec2_impl(const T& x_, const T& y_)
		: x(x_), y(y_) {}

	template<typename T>
	vec2_impl<T>::vec2_impl(const vec2_impl& p1, const vec2_impl& p2)
		: x(p2.x - p1.x), y(p2.y - p1.y) {}

	template<typename T>
	template<typename Q>
	vec2_impl<T>::vec2_impl(const vec2_impl<Q>& o)
		: x(T(o.x)), y(T(o.y)) {}

	template<typename T>
	vec2_impl<T> vec2_impl<T>::operator-() const
	{
		return { -x, -y };
	}

	template<typename T>
	vec2_impl<T> vec2_impl<T>::operator+(const vec2_impl& o) const
	{
		return { x + o.x, y + o.y };
	}

	template<typename T>
	vec2_impl<T> vec2_impl<T>::operator-(const vec2_impl& o) const
	{
		return { x - o.x, y - o.y };
	}

	template<typename T>
	vec2_impl<T> vec2_impl<T>::operator*(const T& val) const
	{
		return { x * val, y * val };
	}

	template<typename T>
	vec2_impl<T> vec2_impl<T>::operator/(const T& val) const
	{
		return { x / val, y / val };
	}

	template<typename T>
	vec2_impl<T>& vec2_impl<T>::operator+=(const vec2_impl& o)
	{
		return *this = (*this) + o;
	}

	template<typename T>
	vec2_impl<T>& vec2_impl<T>::operator-=(const vec2_impl& o)
	{
		return *this = (*this) - o;
	}

	template<typename T>
	vec2_impl<T>& vec2_impl<T>::operator*=(const T& val)
	{
		return *this = (*this) * val;
	}

	template<typename T>
	vec2_impl<T>& vec2_impl<T>::operator/=(const T& val)
	{
		return *this = (*this) / val;
	}

	template<typename T>
	bool vec2_impl<T>::operator==(const vec2_impl& o) const
	{
		return x == o.x && y == o.y;
	}

	template<typename T>
	bool vec2_impl<T>::operator!=(const vec2_impl& o) const
	{
		return !((*this) == o);
	}

	template<typename T>
	bool vec2_impl<T>::operator<(const vec2_impl& o) const
	{
		return x != o.x ? x < o.x : y < o.y;
	}

	template<typename T>
	bool vec2_impl<T>::operator>(const vec2_impl& o) const
	{
		return x != o.x ? x > o.x : y > o.y;
	}
}

#endif
