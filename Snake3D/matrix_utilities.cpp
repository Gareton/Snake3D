#include "matrix_utilities.h"
#include "vector_utilities.h"
#include "gutilities.h"
#include <stdexcept>

namespace gmt
{
	mat4 translate(const vec3& v)
	{
		return mat4({ { 1.0f, 0.0f, 0.0f, v.x  },
					  { 0.0f, 1.0f, 0.0f, v.y  },
					  { 0.0f, 0.0f, 1.0f, v.z  },
					  { 0.0f, 0.0f, 0.0f, 1.0f } });
	}

	mat4 rotateX(sk_float angle)
	{
		return mat4({ { 1.0f, 0.0f,        0.0f,       0.0f },
					  { 0.0f, cos(angle), -sin(angle), 0.0f },
				      { 0.0f, sin(angle),  cos(angle), 0.0f },
					  { 0.0f, 0.0f,        0.0f,       1.0f } });
	}

	mat4 rotateY(sk_float angle)
	{
		return mat4({ {  cos(angle), 0.0f, sin(angle), 0.0f },
					  {  0.0f,       1.0f, 0.0f,       0.0f },
					  { -sin(angle), 0.0f, cos(angle), 0.0f },
				      {  0.0f,       0.0f, 0.0f,       1.0f } });
	}

	mat4 rotateZ(sk_float angle)
	{
		return mat4({ { cos(angle), -sin(angle), 0.0f, 0.0f },
			          { sin(angle),  cos(angle), 0.0f, 0.0f },
			          { 0.0f,        0.0f,       1.0f, 0.0f },
			          { 0.0f,        0.0f,       0.0f, 1.0f } });
	}

	mat4 rotate(sk_float angle, const vec3& axis)
	{
		if (angle == GLF_ZERO)
			return mat4(1.0f);

		if (axis.x == GLF_ZERO && axis.z == GLF_ZERO)
			return rotateY(angle);

		vec3 p = { axis.x, 0.0f, axis.z };
		vec3 g = { 0.0f,   0.0f, 1.0f };

		const sk_float beta = gmt::angle(p, g);
		const sk_float theta = gmt::angle(axis, p);

		mat4 res(1.0f);

		res *= rotateY(beta);
		res *= rotateX(-theta);
		res *= rotateZ(angle);
		res *= rotateX(theta);
		res *= rotateY(-beta);

		return res;
	}

	mat4 scale(sk_float scalar)
	{
		return mat4({ { scalar, 0.0f,   0.0f,   0.0f },
				      { 0.0f,   scalar, 0.0f,   0.0f },
					  { 0.0f,   0.0f,   scalar, 0.0f },
			          { 0.0f,   0.0f,   0.0f,   1.0f } });
	}

	mat4 scale(const vec3& v)
	{
		return mat4({ { v.x,  0.0f, 0.0f, 0.0f },
			          { 0.0f, v.y,  0.0f, 0.0f },
			          { 0.0f, 0.0f, v.z,  0.0f },
			          { 0.0f, 0.0f, 0.0f, 1.0f } });
	}

	mat4 perspective(sk_float fov, sk_float widthToHeightRatio, sk_float nearPlane, sk_float farPlane)
	{
		sk_float k = widthToHeightRatio;
		sk_float tg = tan(fov * 0.5f);

		sk_float gdiv = sqrt(1.0f - sqr(k) * sqr(tg));

		if (gdiv == GLF_ZERO)
			throw std::runtime_error("division by zero");

		sk_float g = (2.0f * tg) / gdiv;
		sk_float e = nearPlane;
		sk_float f = farPlane;

		if (e == f || g == GLF_ZERO || k == GLF_ZERO || e == GLF_ZERO)
			throw std::runtime_error("division by zero");

		return mat4({ {2.0f / (g * k), 0.0f    , 0.0f               , 0.0f                       },
					  {0.0f          , 2.0f / g, 0.0f               , 0.0f                       },
					  {0.0f          , 0.0f    , (e + f) / (e - f)  , (2.0f * e * f) / (e - f)	 },
					  {0.0f          , 0.0f    , -1.0f              , 0.0f                       } });
	}

	mat4 ortho(sk_float minX, sk_float maxX, sk_float minY, sk_float maxY)
	{
		sk_float dx = (maxX - minX);
		sk_float dy = (maxY - minY);
		sk_float xmul = 1.0f / dx;
		sk_float ymul = 1.0f / dy;

		return mat4({ { 2.0f * xmul, 0.0f,        0.0f, -minX * xmul * 2.0f - 1.0f },
					  { 0.0f,        2.0f * ymul, 0.0f, -minY * ymul * 2.0f - 1.0f },
					  { 0.0f,        0.0f,        1.0f,  0.0f                      },
					  { 0.0f,        0.0f,        0.0f,  1.0f                      } });
	}
}