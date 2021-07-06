#include "directions.h"

DIRECTION deduceDir(const gmt::vec3i& v)
{
	if (v.x)
		return v.x > 0 ? EAST : WEST;

	if (v.y)
		return v.y > 0 ? UP : DOWN;

	return v.z > 0 ? SOUTH : NORTH;
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