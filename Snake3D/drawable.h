#ifndef DRAWABLE
#define DRAWABLE
#include <cmath>
#include "gmath.h"

class Drawable 
{
public:
	virtual void draw(const gmt::mat4& projection, const gmt::mat4& view) = 0;
	virtual void update(double_t deltaTime) = 0;
};

#endif
