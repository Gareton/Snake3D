#ifndef APPLE_SPAWNER_H
#define APPLE_SPAWNER_H
#include "grid.h"
#include "voxelApple.h"
#include  "snake.h"

class AppleSpawner : public VoxelApple
{
public:
	AppleSpawner(const Grid& grid, const Snake& snake);

	void respawn();
private:
	const Grid &_grid;
	const Snake &_snake;
};

#endif
