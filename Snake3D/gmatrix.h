#ifndef GMATRIX_H
#define GMATRIX_H
#include "skTypes.h"
#include <cassert>

namespace gmt
{
	template<typename T, sk_uint N, sk_uint M>
	class mat
	{
	public:
		mat() = default;
		virtual ~mat() {}
		mat(const mat& o);
		mat& operator=(const mat& o);
		mat(const T(&ar)[N][M]);
		explicit mat(const T& diagonalValue);

		mat(mat&& o);
		mat& operator=(mat&& o);

		mat operator+(const mat& o) const;
		mat operator-() const;
		mat operator-(const mat& o) const;

		template<sk_uint Q>
		mat<T, N, Q> operator*(const mat<T, M, Q>& o) const;

		template<sk_uint Q>
		mat<T, N, Q>& operator*=(const mat<T, M, Q>& o);

		T* operator[](sk_uint row);
		const T* operator[](sk_uint row) const;

	private:
		T _data[N][M] = {};
	};

	template<typename T, sk_uint N, sk_uint M>
	gmt::mat<T, N, M>::mat(const mat& o)
	{
		if (this == &o)
			return;

		for (sk_uint i = 0; i < N; ++i)
			for (sk_uint j = 0; j < M; ++j)
				_data[i][j] = o._data[i][j];
	}

	template<typename T, sk_uint N, sk_uint M>
	mat<T, N, M>& mat<T, N, M>::operator=(const mat& o)
	{
		if (this == &o)
			return *this;

		for (sk_uint i = 0; i < N; ++i)
			for (sk_uint j = 0; j < M; ++j)
				_data[i][j] = o._data[i][j];

		return *this;
	}

	template<typename T, sk_uint N, sk_uint M>
	mat<T, N, M>::mat(const T(&ar)[N][M])
	{
		for (sk_uint i = 0; i < N; ++i)
			for (sk_uint j = 0; j < M; ++j)
				_data[i][j] = ar[i][j];
	}

	template<typename T, sk_uint N, sk_uint M>
	mat<T, N, M>::mat(const T& diagonalValue)
	{
		static_assert(N == M, "You can't initialize non square matrix with diagonal constructor");

		for (sk_uint i = 0; i < N; ++i)
			_data[i][i] = diagonalValue;
	}

	template<typename T, sk_uint N, sk_uint M>
	mat<T, N, M>::mat(mat&& o)
	{
		for (sk_uint i = 0; i < N; ++i)
			for (sk_uint j = 0; j < M; ++j)
				_data[i][j] = o._data[i][j];
	}

	template<typename T, sk_uint N, sk_uint M>
	mat<T, N, M>& mat<T, N, M>::operator=(mat&& o)
	{
		for (sk_uint i = 0; i < N; ++i)
			for (sk_uint j = 0; j < M; ++j)
				_data[i][j] = o._data[i][j];

		return *this;
	}

	template<typename T, sk_uint N, sk_uint M>
	mat<T, N, M> mat<T, N, M>::operator+(const mat& o) const
	{
		mat<T, N, M> rval;

		for (sk_uint i = 0; i < N; ++i)
			for (sk_uint j = 0; j < M; ++j)
				rval._data[i][j] = _data[i][j] + o._data[i][j];

		return std::move(rval);
	}

	template<typename T, sk_uint N, sk_uint M>
	mat<T, N, M> mat<T, N, M>::operator-() const
	{
		mat<T, N, M> rval;

		for (sk_uint i = 0; i < N; ++i)
			for (sk_uint j = 0; j < M; ++j)
				rval._data[i][j] = -_data[i][j];

		return std::move(rval);
	}

	template<typename T, sk_uint N, sk_uint M>
	mat<T, N, M> mat<T, N, M>::operator-(const mat& o) const
	{
		return (*this) + (-o);
	}

	template<typename T, sk_uint N, sk_uint M>
	T* mat<T, N, M>::operator[](sk_uint row)
	{
		return _data[row];
	}

	template<typename T, sk_uint N, sk_uint M>
	const T* mat<T, N, M>::operator[](sk_uint row) const
	{
		return _data[row];
	}

	template<typename T, sk_uint N, sk_uint M>
	template<sk_uint Q>
	mat<T, N, Q> mat<T, N, M>::operator*(const mat<T, M, Q>& o) const
	{
		mat<T, N, Q> rval;

		for (sk_uint i = 0; i < N; ++i)
			for (sk_uint j = 0; j < Q; ++j)
				for (sk_uint k = 0; k < M; ++k)
					rval[i][j] += _data[i][k] * o[k][j];

		return std::move(rval);
	}

	template<typename T, sk_uint N, sk_uint M>
	template<sk_uint Q>
	mat<T, N, Q>& mat<T, N, M>::operator*=(const mat<T, M, Q>& o)
	{
		return *this = (*this) * o;
	}

	using mat2f = mat<sk_float, 2, 2>;
	using mat3f = mat<sk_float, 3, 3>;
	using mat4f = mat<sk_float, 4, 4>;

	using mat2 = mat2f;
	using mat3 = mat3f;
	using mat4 = mat4f;
}

#endif
