#ifndef DIRECTIONS_H
#define DIRECTIONS_H
#include "gmath.h"

enum DIRECTION { NORTH, EAST, SOUTH, WEST, UP, DOWN };

DIRECTION deduceDir(const gmt::vec3i& v);
DIRECTION snapToClosestDir(const gmt::vec3& v);
gmt::vec3i deduceVec(DIRECTION dir);
DIRECTION oppositeDir(DIRECTION dir);

#endif
