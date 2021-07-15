#ifndef SNAKE_CAMERA_CONTROLLER_H
#define SNAKE_CAMERA_CONTROLLER_H
#include "skTypes.h"
#include "snake.h"
#include "window.h"
#include "camera.h"
#include "snakeControllerInterface.h"

class SnakeCameraController : public SnakeControllerInterface
{
public:
	SnakeCameraController() = delete;
	SnakeCameraController(const Camera& camera);

	void processSnakeMovement(const Window& window, Snake& snake) override;
private:
	const Camera* _camera;
};

#endif