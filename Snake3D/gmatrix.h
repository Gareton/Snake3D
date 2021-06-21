#ifndef GMATRIX_H
#define GMATRIX_H
#include "skTypes.h"
#include "gmatrix_impl.h"

namespace gmt
{
	using mat2f = mat<sk_float, 2, 2>;
	using mat3f = mat<sk_float, 3, 3>;
	using mat4f = mat<sk_float, 4, 4>;

	using mat2 = mat2f;
	using mat3 = mat3f;
	using mat4 = mat4f;
}

#endif
