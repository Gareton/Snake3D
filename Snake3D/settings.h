#ifndef SETTINGS_H
#define SETTINGS_H
#include "gmath.h"
#include <string>

class Settings
{
public:
	Settings() = default;

	gmt::vec3 getClearColor() const;

	gmt::vec3 getCameraTarget() const;
	sk_float getCameraRadius() const;
	sk_float getCameraSensitivity() const;
	sk_float getFov() const;
	sk_float getCameraPitch() const;
	sk_float getCameraYaw() const;
	gmt::vec3 getWorldUp() const;

	gmt::vec3 getGridPos() const;
	sk_uint getGridWidth() const;
	sk_uint getGridHeight() const;
	sk_uint getGridLength() const;
	sk_float getGridCubeSize() const;
	sk_float getGridThickness() const;
	gmt::vec3 getGridColor() const;

	gmt::vec3i getSnakeTailPos() const;
	gmt::vec3i getSnakeHeadPos() const;
	sk_float getSnakeSpeed() const;
	gmt::vec3 getSnakeColor() const;

	std::string getFontPath() const;
private:
	gmt::vec3 _clearColor = { 9.0f / 256.0f, 248.0f / 256.0f, 255.0f / 256.0f };

// Camera 
	gmt::vec3 _cameraTarget = gmt::vec3(0.0f);
	sk_float _cameraRadius = 25.0f;
	sk_float _cameraSensitivity = 0.001f;
	sk_float _fov = gmt::radians(45.0f);
	sk_float _cameraPitch = 0.0f;
	sk_float _cameraYaw = 0.0f;
	gmt::vec3 _worldUp = { 0.0f, 1.0f, 0.0f };

// Grid 
	gmt::vec3 _gridPos = gmt::vec3(0.0f);
	sk_uint _gridWidth = 5;
	sk_uint _gridHeight = 5;
	sk_uint _gridLenght = 5;
	sk_float _gridCubeSize = 2.0f;
	sk_float _gridThickness = 0.06f;
	gmt::vec3 _gridColor = gmt::vec3(0.0f);

// Snake
	gmt::vec3i _snakeTailPos = { 0, 0, 4 };
	gmt::vec3i _snakeHeadPos = { 0, 0, 3 };
	sk_float _snakeSpeed = 5.0f;
	gmt::vec3 _snakeColor = { 0.0f, 1.0f, 0.0f };

// Text renderer
	std::string _fontPath = "fonts/futuram.ttf";
};

#endif
