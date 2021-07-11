#ifndef SNAKE_WORLD_CONTROLLER_H
#define SNAKE_WORLD_CONTROLLER_H
#include "skTypes.h"
#include "snake.h"
#include "window.h"

class SnakeWorldController
{
public:
	void processSnakeMovement(const Window& window, Snake& snake);
protected:
	~SnakeWorldController() {}
};

#endif