#include "appleSpawner.h"

AppleSpawner::AppleSpawner(const Grid& grid, const Snake& snake)
	: VoxelApple({}, 4, grid.getCellSize() * 0.1f, grid.getCellSize() * 0.05f, gmt::vec3{ 0.998f, 0.196f, 0.196f },
				 gmt::vec3{ 0.776f, 0.47f, 0.169f }, gmt::vec3{ 0.36f, 0.718f, 0.27f }), 
	_grid(grid), _snake(snake)
{
	respawn();
}

void AppleSpawner::respawn()
{
	for (sk_uint i = 0; i < 100; ++i)
	{
		gmt::vec3i pos(gmt::vec3ui{ gmt::random() % _grid.getWidth(), gmt::random() % _grid.getHeight(),
								    gmt::random() % _grid.getLength() });

		if (!_snake.occupyes(pos))
		{
			VoxelApple::setPos(_grid.convertGridPos(pos));
			return;
		}
	}
}