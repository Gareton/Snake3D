#include "menuSelector.h"

MenuSelector::MenuSelector(const std::vector<std::string>& selectableStrs, const std::vector<sk_int>& selectableIDs,
						   const gmt::vec2& ldPos, const gmt::vec2& rdPos)
	: _selectableStrs(selectableStrs), _selectableIDs(selectableIDs),
	  MenuQuad("resources/selector.png", ldPos, rdPos),
	  _textRenderer("fonts/arial.ttf", gmt::ortho(0, 800, 0, 600), 800, 600)
{
	_lx = ldPos.x;
	_ly = ldPos.y;
	_rx = rdPos.x;
	_ry = rdPos.y;
}

void MenuSelector::render()
{
	MenuQuad::render();
	_textRenderer.renderMiddle(_selectableStrs[_currentIndex], gmt::vec2{ _lx + _rx, _ly + _ry } *0.5f);
}

bool MenuSelector::isIn(const gmt::vec2& pos)
{
	return pos.x >= _lx && pos.x <= _rx && pos.y >= _ly && pos.y <= _ry;
}

sk_int MenuSelector::switchToNextSelectable()
{
	return _selectableIDs[_currentIndex = (++_currentIndex) % _selectableIDs.size()];
}