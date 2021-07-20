#include "menuMajorScreen.h"
#include <glad/glad.h>
#include "game.h"
#include <iostream>
#include "menuSettingsScreen.h"

MenuMajorScreen::MenuMajorScreen(MenuCallbacksInterface& callbacks)
	: _callbacks(callbacks), _background("resources/menu_background.jpg", gmt::vec2(0.0f), gmt::vec2(1.0f)),
	  _playButton("PLAY", {0.3f, 0.55f}, {0.65f, 0.75f}),
	  _settingsButton("SETTINGS", { 0.3f, 0.3f }, { 0.65f, 0.5f })
{}

void MenuMajorScreen::render() 
{
	glDisable(GL_DEPTH_TEST);
	_background.render();
	_playButton.render();
	_settingsButton.render();
	glEnable(GL_DEPTH_TEST);
}

MenuScreen* MenuMajorScreen::processClick(sk_float xPos, sk_float yPos) 
{
	if (_playButton.isIn({ xPos, yPos }))
		_callbacks.switchGameStatus(GAME_RUNNING);

	if (_settingsButton.isIn({ xPos, yPos }))
		return new MenuSettingsScreen(_callbacks);

	return this;
}

void MenuMajorScreen::updateCursorPos(sk_float xPos, sk_float yPos) 
{
}