#ifndef SNAKE_H
#define SNAKE_H
#include "gameObject.h"
#include "straightParallelepiped.h"
#include "gmath.h"
#include "grid.h"
#include <deque>
#include <set>
#include "skTypes.h"
#include "directions.h"

class Snake : public GameObject
{
public:
	Snake(const Grid& grid, const gmt::vec3i& tailPos, const gmt::vec3i& headPos, 
		  sk_float speed = 5.0f, const gmt::vec3& color = {0.0f, 1.0f, 0.0f});

	void draw(const gmt::mat4& projection, const gmt::mat4& view) override;
	void update(sk_double dt) override;

	void grow(sk_float dLength);
	void setDirection(DIRECTION dir);

	bool occupyes(gmt::vec3i pos) const;
	sk_uint occupyedCount(gmt::vec3i pos) const;
	gmt::vec3i getHeadPos() const;
	gmt::vec3i getTailPos() const;
	gmt::vec3 getWorldHeadPos() const;
	gmt::vec3 getWorldTailPos() const;
private:
	void drawCube(const gmt::vec3i& pos, const gmt::mat4& projection, const gmt::mat4& view);
	void drawCubeSlice(const gmt::vec3i& pos, DIRECTION sliceDir, sk_float fill, 
					   const gmt::mat4& projection, const gmt::mat4& view);

	gmt::vec3i nextPos(gmt::vec3i pos, DIRECTION dir);

	const Grid& _grid;

	sk_float _speed;
	gmt::vec3 _color;
	std::deque<gmt::vec3i> _segments;
	std::multiset<gmt::vec3i> _segmentsSet;
	std::deque<DIRECTION> _directions;
	DIRECTION _nextDir;
	sk_float _tailFill = 1.0f, _headFill = 1.0f;
	sk_float _growSpeed = 1.0f;
	sk_float _needsToGrow = 0.0f;
	
	bge::StraightParallelepiped _segment;
};

#endif
