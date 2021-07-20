#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H
#include "menuQuad.h"
#include "textRenderer.h"

class MenuButton : public MenuQuad
{
public:
	MenuButton(const std::string& text, const gmt::vec2& ldPos, const gmt::vec2& rdPos);

	void render();

	bool isIn(const gmt::vec2& pos);
private:
	std::string _text;
	bge::TextRenderer _textRenderer;
	sk_float _lx, _rx, _ly, _ry;
};

#endif
