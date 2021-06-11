#ifndef GAME_H
#define GAME_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <memory>
#include "gmath.h"
#include "grid.h"
#include "window.h"
#include "camera.h"
#include "textRenderer.h"
#include "snake.h"
#include "skTypes.h"
#include "voxelApple.h"

class Game {
public:
	Game(Window& window);
	Game(const Game& o) = delete;
	Game& operator=(const Game& o) = delete;
	void run();

	void framebufferSizeCallback(GLFWwindow* window, sk_uint width, sk_uint height);
	void mouseCallback(GLFWwindow* window, sk_double xpos, sk_double ypos);
	void scrollCallback(GLFWwindow* window, sk_double xoffset, sk_double yoffset);																		
private:				
	void updateScene();
	void renderFrame();	
	void processInput();																								

	Window &_window;
	Camera _camera;
	TextRenderer _textRenderer;
	const gmt::vec4f _clearColor = { 9.0f / 256.0f, 248.0f / 256.0f, 255.0f / 256.0f, 1.0f };	
	Grid _grid;
	Snake _snake;
	sk_double _deltaTime;
	VoxelApple _apple;
	bool _mouseCallbackEnabled = true;
	bool _gameOver = false;
	sk_uint _score = 0;
};

#endif
