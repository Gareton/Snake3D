#include "menuSettingsScreen.h"
#include "menuMajorScreen.h"
#include "game.h"

MenuSettingsScreen::MenuSettingsScreen(MenuCallbacksInterface& callbacks)
	: _callbacks(callbacks),
	  _background("resources/general_background.jpg", {0.0f, 0.0f}, {1.0f, 1.0f}),
	  _backButton("BACK", { 0.3f, 0.3f }, { 0.65f, 0.5f }),
	_controllerSelector({ "Camera Controller", "World Controller" }, { CameraController, WorldController }, 
					    {0.15f, 0.6f}, {0.8f, 0.8f})
{}

void MenuSettingsScreen::MenuSettingsScreen::render()
{
	glDisable(GL_DEPTH_TEST);
	_background.render();
	_backButton.render();
	_controllerSelector.render();
	glEnable(GL_DEPTH_TEST);
}

MenuScreen* MenuSettingsScreen::processClick(sk_float xPos, sk_float yPos)
{
	if (_backButton.isIn({ xPos, yPos }))
		return new MenuMajorScreen(_callbacks);

	if (_controllerSelector.isIn({ xPos, yPos }))
		_callbacks.switchSnakeController(SNAKE_CONTROLLER_TYPE(_controllerSelector.switchToNextSelectable()));

	return this;
}

void MenuSettingsScreen::updateCursorPos(sk_float xPos, sk_float yPos)
{

}