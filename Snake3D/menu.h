#ifndef MENU_H
#define MENU_H
#include "gmath.h"
#include "menuCallbacksInterface.h"
#include "menuScreen.h"
#include <memory>

class Menu
{
public:
	Menu(MenuCallbacksInterface& callbacks);

	void render();

	void processClick(sk_float xPos, sk_float yPos);
	void updateCursorPos(sk_float xPos, sk_float yPos);

private:
	MenuCallbacksInterface& _callbacks;
	std::unique_ptr<MenuScreen> _currentScreen;
};

#endif
