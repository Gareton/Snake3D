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
#include "appleSpawner.h"
#include "windowCallbacksInterface.h"
#include "settings.h"
#include "collisions.h"

template<class SnakeControllingPolicy>
class Game : public WindowCallbacksInterface, 
			 public SnakeControllingPolicy
{
public:
	Game(Window& window, const Settings& settings);
	Game(const Game& o) = delete;
	Game& operator=(const Game& o) = delete;

	void run();

	const Camera& getCamera() const;

	void resizeCallback(sk_uint width, sk_uint height) override;
	void mouseCallback(sk_double xpos, sk_double ypos) override;
	void scrollCallback(sk_double xoffset, sk_double yoffset) override;
private:
	void onUpdate();
	void onRender();
	void onRenderScene();
	void onRenderText();
	void onCollisions();

	void processInput();

	Window &_window;
	const Settings& _settings;
	Camera _camera;
	Grid _grid;
	Snake _snake;
	AppleSpawner _appleSpawner;
	bge::TextRenderer _textRenderer;

	std::vector<std::reference_wrapper<Drawable>> _drawables;
	std::vector<std::reference_wrapper<Updatable>> _updatables;

	gmt::vec3 _clearColor;
	bool _mouseCallbackEnabled = true;
	bool _gameOver = false;
	sk_uint _score = 0;

	sk_double _deltaTime;
};

template<class SnakeControllingPolicy>
Game<SnakeControllingPolicy>::Game(Window& window, const Settings& settings)
	: _window(window), _settings(settings),
	_camera(settings.getCameraTarget(), settings.getCameraRadius(), settings.getCameraSensitivity(), settings.getFov(),
		settings.getCameraPitch(), settings.getCameraYaw(), settings.getWorldUp()),
	_grid(settings.getGridPos(), settings.getGridWidth(), settings.getGridHeight(), settings.getGridLength(),
		settings.getGridCubeSize(), settings.getGridThickness(), settings.getGridColor()),
	_snake(_grid, settings.getSnakeTailPos(), settings.getSnakeHeadPos(), settings.getSnakeSpeed(), settings.getSnakeColor()),
	_appleSpawner(_grid, _snake),
	_textRenderer(settings.getFontPath(), gmt::ortho(0.0f, _window.getWidth(), 0.0f, _window.getHeight()),
		_window.getWidth(), _window.getHeight()),
	_clearColor(settings.getClearColor())
{
	_window.setCallbacks(*this);

	_drawables.push_back(std::ref(_grid));
	_drawables.push_back(std::ref(_snake));
	_drawables.push_back(std::ref(_appleSpawner));

	_updatables.push_back(std::ref(_snake));
}

template<class SnakeControllingPolicy>
void Game<SnakeControllingPolicy>::run()
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

template<class SnakeControllingPolicy>
const Camera& Game<SnakeControllingPolicy>::getCamera() const
{
	return _camera;
}

template<class SnakeControllingPolicy>
void Game<SnakeControllingPolicy>::resizeCallback(sk_uint width, sk_uint height)
{
	_window.setWidth(width);
	_window.setHeight(height);
	_textRenderer.setProjectionMatrix(gmt::ortho(0.0f, width, 0.0f, height));
	_textRenderer.setWindowSize(width, height);
}

template<class SnakeControllingPolicy>
void Game<SnakeControllingPolicy>::mouseCallback(sk_double xpos, sk_double ypos)
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

template<class SnakeControllingPolicy>
void Game<SnakeControllingPolicy>::scrollCallback(sk_double xoffset, sk_double yoffset)
{
	if (!_gameOver)
		_camera.zoom(-yoffset);
}

template<class SnakeControllingPolicy>
void Game<SnakeControllingPolicy>::onUpdate()
{
	if (_gameOver)
		return;

	for (Updatable& updatable : _updatables)
		updatable.update(_deltaTime);
}

template<class SnakeControllingPolicy>
void Game<SnakeControllingPolicy>::onRender()
{
	if (!_gameOver)
	{
		onRenderScene();
		onRenderText();
	}
	else
	{
		_textRenderer.renderMiddleDown("Game Over", { 0.5f, 0.5f }, 3.4f, gmt::vec3{ 1.0f, 0.314f, 0.016f });
		_textRenderer.renderMiddleUp(std::string("Your final score is: " + std::to_string(_score)), { 0.5f, 0.4f }, 1.9f);
		_clearColor = gmt::vec3{ 0.016f, 1.0f, 0.443f };
	}
}

template<class SnakeControllingPolicy>
void Game<SnakeControllingPolicy>::onRenderScene()
{
	gmt::mat4 projection = gmt::perspective(_camera.getFov(), (sk_double)_window.getWidth() / _window.getHeight(), 0.1f, 100.0f);

	for (Drawable& drawable : _drawables)
		drawable.draw(projection, _camera.getViewMatrix());
}

template<class SnakeControllingPolicy>
void Game<SnakeControllingPolicy>::onRenderText()
{
	_textRenderer.renderUpRight(std::string("Score: ") + std::to_string(_score), { 0.95f, 0.99f }, 0.8f);
}

template<class SnakeControllingPolicy>
void Game<SnakeControllingPolicy>::onCollisions()
{
	if (_gameOver)
		return;

	if (CollisionDetecter::selfCollide(_snake))
		_gameOver = true;

	if (CollisionDetecter::collide(_snake, _appleSpawner))
	{
		_appleSpawner.respawn();
		_snake.grow(_grid.getCellSize());
		++_score;
	}
}

template<class SnakeControllingPolicy>
void Game<SnakeControllingPolicy>::processInput()
{
	if (_window.isPressed(GLFW_KEY_ESCAPE))
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

	SnakeControllingPolicy::processSnakeMovement(_window, _snake);
}

#endif
