#ifndef MATRIX_UTILITIES
#define MATRIX_UTILITIES
#include "gmatrix.h"
#include "gvector.h"

namespace gmt
{
	mat4 translate(const vec3& v);
	mat4 rotateX(sk_float angle);
	mat4 rotateY(sk_float angle);
	mat4 rotateZ(sk_float angle);
	mat4 rotate(sk_float angle, const vec3& axis);
	mat4 scale(sk_float scalar);
	mat4 scale(const vec3& v);
	mat4 perspective(sk_float fov, sk_float widthToHeightRatio, sk_float nearPlane, sk_float farPlane);
	mat4 ortho(sk_float minX, sk_float maxX, sk_float minY, sk_float maxY);
	
	template<typename T, sk_uint N, sk_uint M>
	const T* valuePtr(const mat<T, N, M> &m)
	{
		return &m[0][0];
	}
}

#endif
