#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H
#include "skTypes.h"

class MenuScreen
{
public:
	virtual void render() = 0;

	virtual MenuScreen* processClick(sk_float xPos, sk_float yPos) = 0;
	virtual void updateCursorPos(sk_float xPos, sk_float yPos) = 0;

	virtual ~MenuScreen() {}
};

#endif
