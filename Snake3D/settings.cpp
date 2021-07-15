#include "settings.h"

// Window
gmt::vec3 Settings::_clearColor = { 9.0f / 256.0f, 248.0f / 256.0f, 255.0f / 256.0f };

// Camera 
gmt::vec3 Settings::_cameraTarget = gmt::vec3(0.0f);
sk_float Settings::_cameraRadius = 25.0f;
sk_float Settings::_cameraSensitivity = 0.001f;
sk_float Settings::_fov = gmt::radians(45.0f);
sk_float Settings::_cameraPitch = 0.0f;
sk_float Settings::_cameraYaw = 0.0f;
gmt::vec3 Settings::_worldUp = { 0.0f, 1.0f, 0.0f };

// Grid 
gmt::vec3 Settings::_gridPos = gmt::vec3(0.0f);
sk_uint Settings::_gridWidth = 5;
sk_uint Settings::_gridHeight = 5;
sk_uint Settings::_gridLenght = 5;
sk_float Settings::_gridCubeSize = 2.0f;
sk_float Settings::_gridThickness = 0.06f;
gmt::vec3 Settings::_gridColor = gmt::vec3(0.0f);

// Snake
gmt::vec3i Settings::_snakeTailPos = { 0, 0, 4 };
gmt::vec3i Settings::_snakeHeadPos = { 0, 0, 3 };
sk_float Settings::_snakeSpeed = 5.0f;
gmt::vec3 Settings::_snakeColor = { 0.0f, 1.0f, 0.0f };

// Text renderer
std::string Settings::_fontPath = "fonts/futuram.ttf";

// ***********************Window***********************
gmt::vec3 Settings::getClearColor()
{
	return _clearColor;
}


// ***********************Camera***********************
gmt::vec3 Settings::getCameraTarget()
{
	return _cameraTarget;
}

sk_float Settings::getCameraRadius()
{
	return _cameraRadius;
}

sk_float Settings::getCameraSensitivity()
{
	return _cameraSensitivity;
}

sk_float Settings::getFov()
{
	return _fov;
}

sk_float Settings::getCameraPitch()
{
	return _cameraPitch;
}

sk_float Settings::getCameraYaw()
{
	return _cameraYaw;
}

gmt::vec3 Settings::getWorldUp()
{
	return _worldUp;
}


// ***********************Grid***********************
gmt::vec3 Settings::getGridPos()
{
	return _gridPos;
}

sk_uint Settings::getGridWidth()
{
	return _gridWidth;
}

sk_uint Settings::getGridHeight()
{
	return _gridHeight;
}

sk_uint Settings::getGridLength()
{
	return _gridLenght;
}

sk_float Settings::getGridCubeSize()
{
	return _gridCubeSize;
}

sk_float Settings::getGridThickness()
{
	return _gridThickness;
}

gmt::vec3 Settings::getGridColor()
{
	return _gridColor;
}


// ***********************Snake***********************
gmt::vec3i Settings::getSnakeTailPos()
{
	return _snakeTailPos;
}

gmt::vec3i Settings::getSnakeHeadPos()
{
	return _snakeHeadPos;
}

sk_float Settings::getSnakeSpeed()
{
	return _snakeSpeed;
}

gmt::vec3 Settings::getSnakeColor()
{
	return _snakeColor;
}


// ***********************TextRenderer***********************
std::string Settings::getFontPath()
{
	return _fontPath;
}