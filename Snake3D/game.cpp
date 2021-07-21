#include "game.h"
#include "snakeCameraController.h"
#include "settings.h"
#include "snakeWorldController.h"

Game::Game(Window& window)
	: _window(window), 
	_snake(_grid),
	_appleSpawner(_grid, _snake),
	_textRenderer(Settings::getFontPath(), gmt::ortho(0.0f, _window.getWidth(), 0.0f, _window.getHeight()),
				  _window.getWidth(), _window.getHeight()),
	_snakeController(std::make_unique<SnakeCameraController>(_camera)),
	_clearColor(Settings::getClearColor()),
	_menu(*this),
	_skybox("resources/space_skybox.png")
{
	_window.setCallbacks(*this);
	
	_drawables.push_back(std::ref(_grid));
	_drawables.push_back(std::ref(_snake));
	_drawables.push_back(std::ref(_appleSpawner));
	_drawables.push_back(std::ref(_skybox));

	_updatables.push_back(std::ref(_snake));
	_updatables.push_back(std::ref(_appleSpawner));
}

void Game::run()
{
	while (!_window.shouldClose())
	{
		static sk_double frameStartTime = 0.0f;
		static sk_double frameEndTime = 0.0f;
		_deltaTime = frameEndTime - frameStartTime;

		frameStartTime = glfwGetTime();

		//TODO: incapsulate into something
		glClearColor(_clearColor.x, _clearColor.y, _clearColor.z, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		processInput();
		onUpdate();
		onCollisions();
		onRender();

		_window.swapBuffers();
		_window.pollEvents();

		frameEndTime = glfwGetTime();
	}
}

const Camera& Game::getCamera() const
{
	return _camera;
}


void Game::resizeCallback(sk_uint width, sk_uint height)
{
	_window.setWidth(width);
	_window.setHeight(height);
	_textRenderer.setProjectionMatrix(gmt::ortho(0.0f, width, 0.0f, height));
	_textRenderer.setWindowSize(width, height);
}

void Game::mouseCallback(sk_double xpos, sk_double ypos)
{
	if (_gameStatus == GAME_OVER)
		return;

	if (_gameStatus == GAME_MENU)
	{
		_lastXCursorPos = xpos;
		_lastYCursorPos = ypos;
		_menu.updateCursorPos(xpos / _window.getWidth(), 1.0f - ypos / _window.getHeight());
		return;
	}

	static sk_double lastXpos = xpos;
	static sk_double lastYpos = ypos;

	sk_float pitchDelta = (lastYpos - ypos) * _camera.getSensitivity();
	sk_float yawDelta = (xpos - lastXpos) * _camera.getSensitivity();

	_camera.changePitch(pitchDelta);
	_camera.changeYaw(yawDelta);	

	lastXpos = xpos;
	lastYpos = ypos;
}

void Game::scrollCallback(sk_double xoffset, sk_double yoffset)
{
	if (_gameStatus == GAME_RUNNING)
		_camera.zoom(-yoffset);
}

void Game::mouseButtonCallback(sk_int button, sk_int action, sk_int mods)
{
	if (_gameStatus != GAME_MENU)
		return;

	static bool prevPress = false;

	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		if (action == GLFW_PRESS)
		{
			if (!prevPress)
			{
				prevPress = true;
				_menu.processClick(_lastXCursorPos / _window.getWidth(), 1.0f - _lastYCursorPos / _window.getHeight());
			}
		}
		else
			prevPress = false;
	}
}

void Game::switchSnakeController(SNAKE_CONTROLLER_TYPE controllerType)
{
	switch (controllerType)
	{
	case CameraController:
		_snakeController.reset(new SnakeCameraController(_camera));
		break;

	case WorldController:
		_snakeController.reset(new SnakeWorldController());
		break;

	default:
		break;
	}
}

void Game::switchGameStatus(GAME_STATUS gameStatus)
{
	_gameStatus = gameStatus;
}

void Game::onUpdate()
{
	if (_gameStatus != GAME_RUNNING)
		return;

	for (Updatable& updatable : _updatables)
		updatable.update(_deltaTime);
}

void Game::onRender()
{
	if (_gameStatus == GAME_RUNNING)
	{
		onRenderScene();
		onRenderText();
	}
	else if (_gameStatus == GAME_MENU)
	{
		_menu.render();
	}
	else if(_gameStatus == GAME_OVER)
	{
		_textRenderer.renderMiddleDown("Game Over", { 0.5f, 0.5f }, 3.4f, gmt::vec3{ 1.0f, 0.314f, 0.016f });

		std::string fourStr = "))0)";

		if (_score != 4)
			fourStr = "";

		_textRenderer.renderMiddleUp(std::string("Your final score is: " + std::to_string(_score)) + fourStr, { 0.5f, 0.4f }, 1.9f);
		_clearColor = gmt::vec3{ 0.016f, 1.0f, 0.443f };
	}
}

void Game::onRenderScene()
{
	gmt::mat4 projection = gmt::perspective(_camera.getFov(), (sk_double)_window.getWidth() / _window.getHeight(), 0.1f, 100.0f);

	for (Drawable& drawable : _drawables)
		drawable.draw(projection, _camera.getViewMatrix());
}

void Game::onRenderText()
{
	_textRenderer.renderUpRight(std::string("Score: ") + std::to_string(_score), { 0.95f, 0.99f }, 0.8f);
}

void Game::onCollisions()
{
	if (_gameStatus != GAME_RUNNING)
		return;

	if (CollisionDetecter::selfCollide(_snake))
		_gameStatus = GAME_OVER;

	if (CollisionDetecter::collide(_snake, _appleSpawner))
	{
		_appleSpawner.respawn();
		_snake.grow(_grid.getCellSize());
		++_score;
	}
}

void Game::processInput()
{

	if (_window.isPressed(GLFW_KEY_ESCAPE))
		_window.close();

	switch (_gameStatus)
	{
	case GAME_MENU:
		_window.setCursorMode(GLFW_CURSOR_NORMAL);
		break;

	case GAME_RUNNING:
		_window.setCursorMode(GLFW_CURSOR_DISABLED);
		break;

	case GAME_OVER:
		_window.setCursorMode(GLFW_CURSOR_DISABLED);
	}

	if (_window.isPressed(GLFW_KEY_LEFT_ALT))
		_window.setCursorMode(GLFW_CURSOR_NORMAL);

	if(_gameStatus == GAME_RUNNING)
		_snakeController->processSnakeMovement(_window, _snake);
}