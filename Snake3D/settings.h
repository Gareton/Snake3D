#ifndef SETTINGS_H
#define SETTINGS_H
#include "gmath.h"
#include <string>

class Settings
{
public:
	Settings() = delete;

	static void loadSettingsFromJSON(const std::string& path);

	static gmt::vec3 getClearColor();

	static gmt::vec3 getCameraTarget();
	static sk_float getCameraRadius();
	static sk_float getCameraSensitivity();
	static sk_float getFov();
	static sk_float getCameraPitch();
	static sk_float getCameraYaw();
	static gmt::vec3 getWorldUp();

	static gmt::vec3 getGridPos();
	static sk_uint getGridWidth();
	static sk_uint getGridHeight();
	static sk_uint getGridLength();
	static sk_float getGridCubeSize();
	static sk_float getGridThickness();
	static gmt::vec3 getGridColor();

	static gmt::vec3i getSnakeTailPos();
	static gmt::vec3i getSnakeHeadPos();
	static sk_float getSnakeSpeed();
	static gmt::vec3 getSnakeColor();

	static std::string getFontPath();
private:
// Window
	static gmt::vec3 _clearColor;

// Camera 
	static gmt::vec3 _cameraTarget;
	static sk_float _cameraRadius;
	static sk_float _cameraSensitivity;
	static sk_float _fov;
	static sk_float _cameraPitch;
	static sk_float _cameraYaw;
	static gmt::vec3 _worldUp;

// Grid 
	static gmt::vec3 _gridPos;
	static sk_uint _gridWidth;
	static sk_uint _gridHeight;
	static sk_uint _gridLenght;
	static sk_float _gridCubeSize;
	static sk_float _gridThickness;
	static gmt::vec3 _gridColor;

// Snake
	static gmt::vec3i _snakeTailPos;
	static gmt::vec3i _snakeHeadPos;
	static sk_float _snakeSpeed;
	static gmt::vec3 _snakeColor;

// Text renderer
	static std::string _fontPath;
};

#endif
