#ifndef MENU_MAJOR_SCREEN_H
#define MENU_MAJOR_SCREEN_H
#include "menuScreen.h"
#include "menuCallbacksInterface.h"
#include "menuQuad.h"
#include "menuButton.h"

class MenuMajorScreen : public MenuScreen
{
public:
	MenuMajorScreen(MenuCallbacksInterface& callbacks);

	void render() override;

	MenuScreen* processClick(sk_float xPos, sk_float yPos) override;
	void updateCursorPos(sk_float xPos, sk_float yPo) override;
private:
	MenuCallbacksInterface& _callbacks;
	MenuQuad _background;
	MenuButton _playButton;
	MenuButton _settingsButton;
};

#endif
