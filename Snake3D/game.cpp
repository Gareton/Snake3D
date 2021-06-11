#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "game.h"
#include "cube.h"

Game::Game(Window& window)
	:_grid({ 0.0f, 0.0f, 0.0f }, 2.0f, 10, 1, 10, 0.04f, { 0.0f, 0.0f, 0.0f, 1.0f }),
	_camera({ 0.0f, 0.0f, 0.0f }, 25.0f, 0.001f, gmt::radians(45.0f), gmt::radians(-87.0f)), _snake(_grid, { 0, 0, 9 }, { 0, 0, 1 }, 5.0f),
	_window(window), _textRenderer("fonts/futuram.ttf"), 
	_apple(gmt::vec3{ 0.0f, 2.0f, 0.0f }, 8, 0.1f, 0.1f, 
		   gmt::vec3{ 0.998f, 0.196f, 0.196f },
		   gmt::vec3{ 0.776f, 0.47f, 0.169f },
		   gmt::vec3{ 0.36f, 0.718f, 0.27f })
{
	glfwSetWindowUserPointer(_window.getWindowPtr(), this);

	auto framebufferSizeCallbackLambda = [](GLFWwindow* window, int width, int height)
	{
		static_cast<Game*>(glfwGetWindowUserPointer(window))->framebufferSizeCallback(window, width, height);
	};

	glfwSetFramebufferSizeCallback(_window.getWindowPtr(), framebufferSizeCallbackLambda);

	auto mouseCallbackLambda = [](GLFWwindow* window, double xpos, double ypos)
	{
		static_cast<Game*>(glfwGetWindowUserPointer(window))->mouseCallback(window, xpos, ypos);
	};

	glfwSetCursorPosCallback(_window.getWindowPtr(), mouseCallbackLambda);

	auto scrollCallbackLambda = [](GLFWwindow* window, double xoffset, double yoffset)
	{
		static_cast<Game*>(glfwGetWindowUserPointer(window))->scrollCallback(window, xoffset, yoffset);
	};

	glfwSetScrollCallback(_window.getWindowPtr(), scrollCallbackLambda);
}

void Game::run()
{
	while (!glfwWindowShouldClose(_window.getWindowPtr()))
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

		glfwSwapBuffers(_window.getWindowPtr());
		glfwPollEvents();

		frameEndTime = glfwGetTime();
	}
}

void Game::updateScene()
{
	if (_gameOver)
		return;

	_snake.update(_deltaTime);

	if (_snake.collided())
		_gameOver = true;
}

void Game::renderFrame()
{
	gmt::mat4 projection = gmt::perspective(_camera.getFov(),
								   (sk_double)_window.getWindowWidth() / _window.getWindowHeight(),
								   0.1f, 100.0f);

	gmt::mat4 view = _camera.getViewMatrix();

	_grid.draw(projection, view);
	_snake.draw(projection, view);
	_apple.draw(projection, view);

	gmt::mat4 textProjection = gmt::ortho(0.0f, _window.getWindowWidth(), 
										  0.0f, _window.getWindowHeight());

	std::string scoreString = std::string("Score: ") + std::to_string(_score);

	_textRenderer.render(scoreString, textProjection, { 800.0f, 750.0f }, 0.8f, gmt::vec3{ 0.0f });
}

void Game::framebufferSizeCallback(GLFWwindow* window, sk_uint width, sk_uint height)
{
	_window.setWindowWidth(width);
	_window.setWindowHeight(height);
	glViewport(0, 0, width, height);
}

void Game::mouseCallback(GLFWwindow* window, sk_double xpos, sk_double ypos)
{
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

void Game::processInput()
{
	GLFWwindow* windowPtr = _window.getWindowPtr();

	if(glfwGetKey(windowPtr, GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(windowPtr, true);

	if (glfwGetKey(windowPtr, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
	{
		glfwSetInputMode(windowPtr, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		_mouseCallbackEnabled = false;
	}
	else
	{
		glfwSetInputMode(windowPtr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		_mouseCallbackEnabled = true;
	}

	if (glfwGetKey(windowPtr, GLFW_KEY_T) == GLFW_PRESS)
		_snake.setDirection(DIRECTION::NORTH);

	if (glfwGetKey(windowPtr, GLFW_KEY_G) == GLFW_PRESS)
		_snake.setDirection(DIRECTION::SOUTH);

	if (glfwGetKey(windowPtr, GLFW_KEY_H) == GLFW_PRESS)
		_snake.setDirection(DIRECTION::EAST);

	if (glfwGetKey(windowPtr, GLFW_KEY_F) == GLFW_PRESS)
		_snake.setDirection(DIRECTION::WEST);

	if (glfwGetKey(windowPtr, GLFW_KEY_C) == GLFW_PRESS)
		_snake.setDirection(DIRECTION::UP);

	if (glfwGetKey(windowPtr, GLFW_KEY_N) == GLFW_PRESS)
		_snake.setDirection(DIRECTION::DOWN);
}

void Game::scrollCallback(GLFWwindow* window, sk_double xoffset, sk_double yoffset)
{
	_camera.zoom(-yoffset);
}