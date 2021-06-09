#ifndef CUBE_H
#define CUBE_H
#include "gmath.h"
#include "drawable.h"
#include "straightParallelepiped.h"

class Cube : Drawable
{
public:
	explicit Cube(float_t size, const gmt::vec3& position = { 0.0f, 0.0f, 0.0f }, 
				  const gmt::vec4 color = {0.0f, 0.0f, 0.0f, 1.0f});
	void draw(const gmt::mat4& projection, const gmt::mat4& view);
	void update(double_t deltaTime);

	void setPosition(const gmt::vec3& position);
private:
	StraightParallelepiped _cube;
};

#endif
