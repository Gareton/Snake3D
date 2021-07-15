#ifndef DRAWABLE
#define DRAWABLE
#include <cmath>
#include "gmath.h"
#include "skTypes.h"

class Drawable 
{
public:
	virtual void draw(const gmt::mat4& projection, const gmt::mat4& view) const = 0;

	virtual ~Drawable() {};
};

#endif
