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
#include "snakeControllerInterface.h"
#include "menu.h"
#include "skybox.h"

enum GAME_STATUS { GAME_MENU, GAME_OVER, GAME_RUNNING };
enum SNAKE_CONTROLLER_TYPE { CameraController, WorldController };

class Game : public WindowCallbacksInterface,
			 public MenuCallbacksInterface
{
public:
	Game(Window& window);
	Game(const Game& o) = delete;
	Game& operator=(const Game& o) = delete;

	void run();

	const Camera& getCamera() const;

	void resizeCallback(sk_uint width, sk_uint height) override;
	void mouseCallback(sk_double xpos, sk_double ypos) override;
	void scrollCallback(sk_double xoffset, sk_double yoffset) override;
	void mouseButtonCallback(sk_int button, sk_int action, sk_int mods) override;

	void switchSnakeController(SNAKE_CONTROLLER_TYPE controllerType) override;
	void switchGameStatus(GAME_STATUS gameStatus) override;
private:
	void onUpdate();
	void onRender();
	void onRenderScene();
	void onRenderText();
	void onCollisions();

	void processInput();

	Window &_window;
	Menu _menu;
	Camera _camera;
	Grid _grid;
	Snake _snake;
	std::unique_ptr<SnakeControllerInterface> _snakeController; 
	AppleSpawner _appleSpawner;
	bge::TextRenderer _textRenderer;
	Skybox _skybox;

	std::vector<std::reference_wrapper<Drawable>> _drawables;
	std::vector<std::reference_wrapper<Updatable>> _updatables;

	gmt::vec3 _clearColor;
	sk_uint _score = 0;

	sk_double _deltaTime;
	GAME_STATUS _gameStatus = GAME_MENU;

	sk_double _lastXCursorPos;
	sk_double _lastYCursorPos;
};

#endif
