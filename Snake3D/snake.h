#ifndef SNAKE_H
#define SNAKE_H
#include "drawable.h"
#include "straightParallelepiped.h"
#include "gmath.h"
#include "grid.h"
#include <deque>
#include <set>

enum DIRECTION{NORTH, EAST, SOUTH, WEST, UP, DOWN};

class Snake : Drawable
{
public:
	Snake(const Grid& grid, const gmt::vec3i& tailPos, const gmt::vec3i& headPos, const float_t speed = 5.0f, 
		  const gmt::vec4& color = {0.0f, 1.0f, 0.0f, 1.0f});
	void draw(const gmt::mat4& projection, const gmt::mat4& view);
	void update(double_t deltaTime);
	void setDirection(DIRECTION dir);
	bool collided() const;

	static const std::vector<gmt::vec3> dirVectors;
private:
	void drawPath(gmt::vec3 p1, gmt::vec3 p2);
	void drawSegment(gmt::vec3 position);
	static std::vector<gmt::vec3> createDirVectors();
	DIRECTION deduceDirection(const gmt::vec3& v);
	DIRECTION opposite(DIRECTION direction);
	float_t goToTarget(float_t canTravel);
	gmt::vec3 moveInDirection(const gmt::vec3 &v, DIRECTION direction, float_t distance);
	void moveTail(float_t distanceTravelled);
	void changeTarget();
	gmt::vec3i toBlockPosition(const gmt::vec3& position);

	const Grid &_grid;
	StraightParallelepiped _segment;
	std::deque<std::deque<gmt::vec3>> _chains;
	const float_t _speed;
	gmt::mat4 _projection;
	gmt::mat4 _view;
	gmt::vec4 _color;
	gmt::vec3i _target;
	DIRECTION _direction;
	std::multiset<gmt::vec3i> _currentPositions;
	bool _collided = false;
};

#endif
