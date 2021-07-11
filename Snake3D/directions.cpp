#include "directions.h"
#include <algorithm>

DIRECTION deduceDir(const gmt::vec3i& v)
{
	if (v.x)
		return v.x > 0 ? EAST : WEST;

	if (v.y)
		return v.y > 0 ? UP : DOWN;

	return v.z > 0 ? SOUTH : NORTH;
}

DIRECTION snapToClosestDir(const gmt::vec3& v)
{
	sk_float max = std::max({ abs(v.x), abs(v.y), abs(v.z) });

	if (abs(v.x) == max)
		return deduceDir({ (v.x < 0.0f ? -1 : 1), 0, 0 });
	
	if (abs(v.y) == max)
		return deduceDir({ 0, (v.y < 0.0f ? -1 : 1), 0 });

	return deduceDir({ 0, 0, (v.z < 0.0f ? -1 : 1) });
}

gmt::vec3i deduceVec(DIRECTION dir)
{
	switch (dir)
	{
	case UP:
		return {0, 1, 0};

	case DOWN:
		return {0, -1, 0};

	case EAST:
		return {1, 0, 0};

	case WEST:
		return {-1, 0, 0};

	case NORTH:
		return {0, 0, -1};

	case SOUTH:
		return {0, 0, 1};
	}

	return { 0, 0, 0 };
}

DIRECTION oppositeDir(DIRECTION dir)
{
	switch (dir)
	{
	case UP:
		return DOWN;

	case DOWN:
		return UP;

	case EAST:
		return WEST;

	case WEST:
		return EAST;

	case NORTH:
		return SOUTH;

	case SOUTH:
		return NORTH;
	}

	return NORTH;
}