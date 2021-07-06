#include "settings.h"

gmt::vec3 Settings::getClearColor() const
{
	return _clearColor;
}

gmt::vec3 Settings::getCameraTarget() const
{
	return _cameraTarget;
}

sk_float Settings::getCameraRadius() const
{
	return _cameraRadius;
}

sk_float Settings::getCameraSensitivity() const
{
	return _cameraSensitivity;
}

sk_float Settings::getFov() const
{
	return _fov;
}

sk_float Settings::getCameraPitch() const
{
	return _cameraPitch;
}

sk_float Settings::getCameraYaw() const
{
	return _cameraYaw;
}

gmt::vec3 Settings::getWorldUp() const
{
	return _worldUp;
}

gmt::vec3 Settings::getGridPos() const
{
	return _gridPos;
}

sk_uint Settings::getGridWidth() const
{
	return _gridWidth;
}

sk_uint Settings::getGridHeight() const
{
	return _gridHeight;
}

sk_uint Settings::getGridLength() const
{
	return _gridLenght;
}

sk_float Settings::getGridCubeSize() const
{
	return _gridCubeSize;
}

sk_float Settings::getGridThickness() const
{
	return _gridThickness;
}

gmt::vec3 Settings::getGridColor() const
{
	return _gridColor;
}

gmt::vec3i Settings::getSnakeTailPos() const
{
	return _snakeTailPos;
}

gmt::vec3i Settings::getSnakeHeadPos() const
{
	return _snakeHeadPos;
}
sk_float Settings::getSnakeSpeed() const
{
	return _snakeSpeed;
}

gmt::vec3 Settings::getSnakeColor() const
{
	return _snakeColor;
}

std::string Settings::getFontPath() const
{
	return _fontPath;
}