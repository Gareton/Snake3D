#ifndef COLLISIONS_H
#define COLLISIONS_H
#include "snake.h"
#include "voxelApple.h"

namespace CollisionDetecter
{
	bool collide(const Snake& snake, const VoxelApple& apple);
	bool selfCollide(const Snake& snake);
}
#endif
