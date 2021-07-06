#include "collisions.h"

namespace CollisionDetecter
{
	bool collide(const Snake& snake, const VoxelApple& apple)
	{
		if (gmt::distance(snake.getWorldHeadPos(), apple.getPos()) == 0.0f)
			return true;

		return false;
	}

	bool selfCollide(const Snake& snake)
	{
		if (snake.occupyedCount(snake.getHeadPos()) > 1)
			return true;

		return false;
	}
}