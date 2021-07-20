#include "menuButton.h"
#include "gmath.h"

MenuButton::MenuButton(const std::string& text, const gmt::vec2& ldPos, const gmt::vec2& rdPos)
	: _text(text),
	  MenuQuad("resources/button.jpg", ldPos, rdPos),
	  _textRenderer("fonts/arial.ttf", gmt::ortho(0, 800, 0, 600), 800, 600)
{
	_lx = ldPos.x;
	_ly = ldPos.y;
	_rx = rdPos.x;
	_ry = rdPos.y;
}

void MenuButton::render()
{
	MenuQuad::render();
	_textRenderer.renderMiddle(_text, gmt::vec2{ _lx + _rx, _ly + _ry } * 0.5f);
}

bool MenuButton::isIn(const gmt::vec2& pos)
{
	return pos.x >= _lx && pos.x <= _rx && pos.y >= _ly && pos.y <= _ry;
}