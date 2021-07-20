#ifndef MENU_SETTINGS_SCREEN_H
#define MENU_SETTINGS_SCREEN_H
#include "menuScreen.h"
#include "menuCallbacksInterface.h"
#include "menuButton.h"
#include "menuSelector.h"

class MenuSettingsScreen : public MenuScreen
{
public:
	MenuSettingsScreen(MenuCallbacksInterface& callbacks);

	void render() override;

	MenuScreen* processClick(sk_float xPos, sk_float yPos) override;
	void updateCursorPos(sk_float xPos, sk_float yPos) override;
private:
	MenuCallbacksInterface& _callbacks;
	MenuQuad _background;
	MenuButton _backButton;
	MenuSelector _controllerSelector;
};

#endif
