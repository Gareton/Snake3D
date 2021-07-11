#include "snakeWorldController.h"

void SnakeWorldController::processSnakeMovement(const Window& window, Snake& snake)
{
	if (window.isPressed(GLFW_KEY_T))
		snake.setDirection(DIRECTION::NORTH);

	if (window.isPressed(GLFW_KEY_G))
		snake.setDirection(DIRECTION::SOUTH);

	if (window.isPressed(GLFW_KEY_H))
		snake.setDirection(DIRECTION::EAST);

	if (window.isPressed(GLFW_KEY_F))
		snake.setDirection(DIRECTION::WEST);

	if (window.isPressed(GLFW_KEY_C))
		snake.setDirection(DIRECTION::UP);

	if (window.isPressed(GLFW_KEY_N))
		snake.setDirection(DIRECTION::DOWN);
}