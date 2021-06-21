#include "gvector3_utilities.h"
#include "gutilities.h"

namespace gmt
{
	sk_float angle(vec3 v1, vec3 v2)
	{
		return atan2(dot(cross(v1, v2), normal(v1, v2)), dot(v1, v2));
	}

	sk_float dot(const vec3& v1, const vec3& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	vec3 cross(const vec3& v1, const vec3& v2)
	{
		return { v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x };
	}

	sk_float distance(const vec3& p1, const vec3& p2)
	{
		return sqrt(sqr(p1.x - p2.x) + sqr(p1.y - p2.y) + sqr(p1.z - p2.z));
	}

	sk_float length(const vec3& v)
	{
		return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	}

	vec3 normalize(const vec3& v)
	{
		sk_float len = length(v);

		return len == GLF_ZERO ? v : v / len;
	}

	vec3 normal(const vec3& v1, const vec3& v2)
	{
		return normalize(cross(v1, v2));
	}

	vec3 middle(const vec3& p1, const vec3& p2)
	{
		return p1 + vec3(p1, p2) * 0.5f;
	}
}