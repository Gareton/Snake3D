#ifndef CUBE_H
#define CUBE_H
#include "gmath.h"
#include "drawable.h"
#include "straightParallelepiped.h"
#include "skTypes.h"

class Cube : Drawable
{
public:
	explicit Cube(sk_float size, const gmt::vec3& position = { 0.0f, 0.0f, 0.0f }, 
				  const gmt::vec4 color = {0.0f, 0.0f, 0.0f, 1.0f});
	void draw(const gmt::mat4& projection, const gmt::mat4& view);
	void update(sk_double deltaTime);

	void setPosition(const gmt::vec3& position);
private:
	StraightParallelepiped _cube;
};

#endif
