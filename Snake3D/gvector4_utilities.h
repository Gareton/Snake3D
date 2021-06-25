#ifndef GVECTOR4_UTILITIES_H
#define GVECTOR4_UTILITIES_H
#include "gvector.h"

namespace gmt
{
	template<typename T>
	const T* valuePtr(const vec4_impl<T>& v)
	{
		return &v[0];
	}
}
#endif
