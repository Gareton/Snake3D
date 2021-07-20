#ifndef MENU_SELECTOR
#define MENU_SELECTOR
#include "menuQuad.h"
#include <vector>
#include <string>
#include "textRenderer.h"

class MenuSelector : public MenuQuad
{
public:
	MenuSelector(const std::vector<std::string>& selectableStrs, const std::vector<sk_int>& selectableIDs, 
			     const gmt::vec2& ldPos, const gmt::vec2& rdPos);

	void render();

	bool isIn(const gmt::vec2& pos);

	sk_int switchToNextSelectable();

private:
	sk_int _currentIndex = 0;
	std::vector<std::string> _selectableStrs;
	std::vector<sk_int> _selectableIDs;
	bge::TextRenderer _textRenderer;
	sk_float _lx, _rx, _ly, _ry;
};

#endif
