#ifndef SNAKE_CONTROLLER_INTERFACE
#define SNAKE_CONTROLLER_INTERFACE

class SnakeControllerInterface
{
public:
	virtual ~SnakeControllerInterface() {}
	virtual void processSnakeMovement(const Window& window, Snake& snake) = 0;
};

#endif
