#ifndef SNAKE_CAMERA_CONTROLLER_H
#define SNAKE_CAMERA_CONTROLLER_H
#include "skTypes.h"
#include "snake.h"
#include "window.h"
#include "camera.h"

class SnakeCameraController
{
public:
	void linkCameraToController(const Camera& camera);
	void processSnakeMovement(const Window& window, Snake& snake);
protected:
	~SnakeCameraController() {}
private:
	const Camera* _camera;
};

#endif