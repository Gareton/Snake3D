#ifndef SNAKE_H
#define SNAKE_H
#include "gameObject.h"
#include "straightParallelepiped.h"
#include "gmath.h"
#include "grid.h"
#include <deque>
#include <set>
#include "skTypes.h"

enum DIRECTION{NORTH, EAST, SOUTH, WEST, UP, DOWN};

class Snake : public GameObject
{
public:
	Snake(const Grid& grid, const gmt::vec3i& tailPos, const gmt::vec3i& headPos, const sk_float speed = 5.0f, 
		  const gmt::vec4& color = {0.0f, 1.0f, 0.0f, 1.0f});
	void draw(const gmt::mat4& projection, const gmt::mat4& view) override;
	void update(sk_double deltaTime) override;

	void grow(sk_float deltaLength);

	void setDirection(DIRECTION dir);
	bool collided() const;
	gmt::vec3i getFullHeadCell();
	bool isUsedBySnake(const gmt::vec3i& pos);

	static const std::vector<gmt::vec3> dirVectors;
private:
	void drawPath(gmt::vec3 p1, gmt::vec3 p2);
	void drawSegment(gmt::vec3 position);
	static std::vector<gmt::vec3> createDirVectors();
	DIRECTION deduceDirection(const gmt::vec3& v);
	DIRECTION opposite(DIRECTION direction);
	sk_float goToTarget(sk_float canTravel);
	gmt::vec3 moveInDirection(const gmt::vec3 &v, DIRECTION direction, sk_float distance);
	void moveTail(sk_float distanceTravelled);
	void changeTarget();
	gmt::vec3i toBlockPosition(const gmt::vec3& position);

	const Grid &_grid;
	StraightParallelepiped _segment;
	std::deque<std::deque<gmt::vec3>> _chains;
	const sk_float _speed;
	const sk_float _growSpeed = 0.4f;
	gmt::mat4 _projection;
	gmt::mat4 _view;
	gmt::vec4 _color;
	gmt::vec3i _target;
	DIRECTION _direction;
	std::multiset<gmt::vec3i> _currentPositions;
	bool _collided = false;
	sk_float _lengthToGrow = 0.0f;
};

#endif
