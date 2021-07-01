#ifndef GVECTOR_H
#define GVECTOR_H
#include "gvector2.h"
#include "gvector3.h"
#include "gvector4.h"
#include "skTypes.h"

namespace gmt
{
	using vec2f = vec2_impl<sk_float>;
	using vec3f = vec3_impl<sk_float>;
	using vec4f = vec4_impl<sk_float>;

	using vec2i = vec2_impl<sk_int>;
	using vec3i = vec3_impl<sk_int>;
	using vec4i = vec4_impl<sk_int>;

	using vec2ui = vec2_impl<sk_uint>;
	using vec3ui = vec3_impl<sk_uint>;
	using vec4ui = vec4_impl<sk_uint>;

	using vec2 = vec2f;
	using vec3 = vec3f;
	using vec4 = vec4f;
}

#endif
