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

class Game : public WindowCallbacksInterface
{
public:
	Game(Window& window, const Settings& settings);
	Game(const Game& o) = delete;
	Game& operator=(const Game& o) = delete;

	void run();

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

#endif
