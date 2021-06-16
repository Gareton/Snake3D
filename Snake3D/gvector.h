#ifndef GVECTOR_H
#define GVECTOR_H
#include "gvector2.h"
#include "gvector3.h"
#include "gvector4.h"

namespace gmt 
{	


	template<typename T>
	struct vec3
	{

		T x, y, z;
	};

	template<typename T>
	struct vec4
	{

		T x, y, z, w;
	};
}


#endif
