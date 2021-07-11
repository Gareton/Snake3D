#include "snakeCameraController.h"

void SnakeCameraController::linkCameraToController(const Camera& camera)
{
	_camera = &camera;
}

void SnakeCameraController::processSnakeMovement(const Window& window, Snake& snake)
{
	DIRECTION dirRelativeToWorld = NORTH;

	if (window.isPressed(GLFW_KEY_T))
		dirRelativeToWorld = UP;

	if (window.isPressed(GLFW_KEY_G))
		dirRelativeToWorld = DOWN;

	if (window.isPressed(GLFW_KEY_H))
		dirRelativeToWorld = EAST;

	if (window.isPressed(GLFW_KEY_F))
		dirRelativeToWorld = WEST;

	if (dirRelativeToWorld == NORTH)
		return;

	gmt::vec4 finalVec = gmt::transpose(_camera->getViewMatrix()) * gmt::vec4(gmt::vec3(deduceVec(dirRelativeToWorld)), 0.0f);

	snake.setDirection(snapToClosestDir(gmt::vec3(finalVec.x, finalVec.y, finalVec.z)));
}