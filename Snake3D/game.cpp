#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "game.h"
#include "cube.h"
#include <functional>

Game::Game(Window& window)
	:_grid({ 0.0f, 0.0f, 0.0f }, 2.0f, 10, 1, 10, 0.06f, { 0.0f, 0.0f, 0.0f, 1.0f }),
	_camera({ 0.0f, 0.0f, 0.0f }, 25.0f, 0.001f, gmt::radians(45.0f), gmt::radians(-87.0f)), _snake(_grid, { 0, 0, 9 }, { 0, 0, 6 }, 5.0f),
	_window(window), _textRenderer("fonts/futuram.ttf"), 
	_apple(gmt::vec3{ 0.0f, 2.0f, 0.0f }, 8, 0.1f, 0.1f, 
		   gmt::vec3{ 0.998f, 0.196f, 0.196f },
		   gmt::vec3{ 0.776f, 0.47f, 0.169f },
		   gmt::vec3{ 0.36f, 0.718f, 0.27f })
{
	_window.setCallbacks(*this);
	placeAppleRandomly();
}

void Game::run()
{
	while (!_window.shouldClose())
	{
		static sk_double frameStartTime = 0.0f;
		static sk_double frameEndTime = 0.0f;
		_deltaTime = frameEndTime - frameStartTime;

		frameStartTime = glfwGetTime();

		glClearColor(_clearColor.x, _clearColor.y, _clearColor.z, _clearColor.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		processInput();
		updateScene();
		renderFrame();

		_window.swapBuffers();
		_window.pollEvents();

		frameEndTime = glfwGetTime();
	}
}

void Game::resizeCallback(sk_uint width, sk_uint height) 
{
	_window.setWidth(width);
	_window.setHeight(height);
	glViewport(0, 0, width, height);
}

void Game::mouseCallback(sk_double xpos, sk_double ypos) 
{
	if (_gameOver)
		return;

	static sk_double lastXpos = xpos;
	static sk_double lastYpos = ypos;

	if (_mouseCallbackEnabled)
	{
		sk_float pitchDelta = (lastYpos - ypos) * _camera.getSensitivity();
		sk_float yawDelta = (xpos - lastXpos) * _camera.getSensitivity();

		_camera.changePitch(pitchDelta);
		_camera.changeYaw(yawDelta);
	}

	lastXpos = xpos;
	lastYpos = ypos;
}

void Game::scrollCallback(sk_double xoffset, sk_double yoffset) 
{
	if (!_gameOver)
		_camera.zoom(-yoffset);
}

void Game::updateScene()
{
	if (_gameOver)
		return;

	_snake.update(_deltaTime);

	if (_snake.collided())
		_gameOver = true;

	static bool scoreWasIncremented = false;

	if (!scoreWasIncremented && 
		_snake.getFullHeadCell() == _grid.worldToGridCoordinate(_apple.getPosition()))
	{
		++_score;
		scoreWasIncremented = true;
		placeAppleRandomly();
		_snake.grow(_grid.getCubeSize());
	}
	else
		scoreWasIncremented = false;
}

void Game::renderFrame()
{
	gmt::mat4 projection = gmt::perspective(_camera.getFov(),
								   (sk_double)_window.getWidth() / _window.getHeight(),
								   0.1f, 100.0f);

	gmt::mat4 view = _camera.getViewMatrix();

	if (!_gameOver)
	{
		_grid.draw(projection, view);
		_snake.draw(projection, view);
		_apple.draw(projection, view);
	}

	gmt::mat4 textProjection = gmt::ortho(0.0f, _window.getWidth(), 
										  0.0f, _window.getHeight());

	std::string scoreString = std::string("Score: ") + std::to_string(_score);

	if (!_gameOver)
		_textRenderer.render(scoreString, textProjection, { 800.0f, 750.0f }, 0.8f, gmt::vec3{ 0.0f });

	if (_gameOver)
	{
		_textRenderer.render("Game Over", textProjection, { 78.0f, 420.0f }, 3.4f, gmt::vec3{ 1.0f, 0.314f, 0.016f });
		_textRenderer.render("((((4", textProjection, { 400.0f, 300.0f }, 2.6f, gmt::vec3{ 1.0f, 0.314f, 0.016f });

		scoreString = std::string("Your final score: " + std::to_string(_score));

		_textRenderer.render(scoreString, textProjection, { 90.0f, 160.0f }, 1.9f, gmt::vec3{ 0.0f });
		_clearColor = gmt::vec4{ 0.016f, 1.0f, 0.443f, 1.0f };
	}
}

void Game::processInput()
{
	if(_window.isPressed(GLFW_KEY_ESCAPE))
		_window.close();

	if (_window.isPressed(GLFW_KEY_LEFT_ALT))
	{
		_window.setCursorMode(GLFW_CURSOR_NORMAL);
		_mouseCallbackEnabled = false;
	}
	else
	{
		_window.setCursorMode(GLFW_CURSOR_DISABLED);
		_mouseCallbackEnabled = true;
	}

	if (_window.isPressed(GLFW_KEY_T))
		_snake.setDirection(DIRECTION::NORTH);

	if (_window.isPressed(GLFW_KEY_G))
		_snake.setDirection(DIRECTION::SOUTH);

	if (_window.isPressed(GLFW_KEY_H))
		_snake.setDirection(DIRECTION::EAST);

	if (_window.isPressed(GLFW_KEY_F))
		_snake.setDirection(DIRECTION::WEST);

	if (_window.isPressed(GLFW_KEY_C))
		_snake.setDirection(DIRECTION::UP);

	if (_window.isPressed(GLFW_KEY_N))
		_snake.setDirection(DIRECTION::DOWN);
}

void Game::placeAppleRandomly()
{
	gmt::vec3i appleCoord = { 0, 0, 0 };

	for (sk_uint i = 0; i < 100; ++i)
	{
		appleCoord = gmt::vec3i{ (sk_int)(gmt::random() % _grid.getWidth()),
								 (sk_int)(gmt::random() % _grid.getHeight()),
								 (sk_int)(gmt::random() % _grid.getLength())};

		if (!_snake.isUsedBySnake(_grid.worldToGridCoordinateBruh(_grid.gridToWorldCoordinate(appleCoord))))
		{
			_apple.setPosition(_grid.gridToWorldCoordinateBruh(_grid.worldToGridCoordinateBruh(_grid.gridToWorldCoordinate(appleCoord))));
			break;
		}
	}
}