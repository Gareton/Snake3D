#include "menu.h"
#include "menuMajorScreen.h"

Menu::Menu(MenuCallbacksInterface& callbacks)
	: _callbacks(callbacks), _currentScreen(std::make_unique<MenuMajorScreen>(callbacks))
{}

void Menu::render()
{
	_currentScreen->render();
}

void Menu::processClick(sk_float xPos, sk_float yPos)
{
	MenuScreen* nextScreen = _currentScreen->processClick(xPos, yPos);

	if(_currentScreen.get() != nextScreen)
		_currentScreen.reset(nextScreen);
}

void Menu::updateCursorPos(sk_float xPos, sk_float yPos)
{
	_currentScreen->updateCursorPos(xPos, yPos);
}