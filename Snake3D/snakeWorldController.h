#ifndef SNAKE_WORLD_CONTROLLER_H
#define SNAKE_WORLD_CONTROLLER_H
#include "skTypes.h"
#include "snake.h"
#include "window.h"
#include "snakeControllerInterface.h"

class SnakeWorldController : public SnakeControllerInterface
{
public:
	void processSnakeMovement(const Window& window, Snake& snake) override;
};

#endif