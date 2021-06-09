#include "snake.h"

const std::vector<gmt::vec3> Snake::dirVectors = Snake::createDirVectors();

Snake::Snake(const Grid& grid, const gmt::vec3i& tailPos, const gmt::vec3i& headPos, const float_t speed, const gmt::vec4& color)
	: _grid(grid), _speed(speed), 
	_segment(gmt::vec3(grid.getCubeSize()), { 0.0f, 0.0f, 0.0f }, color), _color(color)
{
	_chains.push_back({});
	_chains.back().push_back(_grid.gridToWorldCoordinate(headPos));
	_chains.back().push_back(_grid.gridToWorldCoordinate(tailPos));
	_currentPositions.insert(headPos);
	_currentPositions.insert(tailPos);

	_target = headPos;
	_direction = deduceDirection(_chains[0].front() - _chains[0].back());
}

void Snake::draw(const gmt::mat4& projection, const gmt::mat4& view)
{
	_projection = projection;
	_view = view;

	for (const auto& chain : _chains)
		for (size_t i = 0; i + 1 < chain.size(); ++i)
			drawPath(chain[i], chain[i + 1]);
}

void Snake::update(double_t deltaTime)
{
	float_t canTravel = deltaTime * _speed;

	while (canTravel > 0.0f)
		canTravel = goToTarget(canTravel);
}

void Snake::setDirection(DIRECTION dir)
{
	if (-dirVectors[dir] != dirVectors[deduceDirection(_grid.gridToWorldCoordinate(_target) - _chains.front().front())])
		_direction = dir;
}

bool Snake::collided() const
{
	return _collided;
}

void Snake::drawPath(gmt::vec3 p1, gmt::vec3 p2)
{
	drawSegment(p1);
	drawSegment(p2);

	if (p1 > p2)
		std::swap(p1, p2);

	p1 += gmt::vec3(_grid.getCubeSize() * 0.5f);

	gmt::vec3i v1 = _grid.worldToGridCoordinate(p1);
	gmt::vec3i v2 = _grid.worldToGridCoordinate(p2);

	if (v1.x != v2.x)
	{
		++v1.x;

		while (v1.x <= v2.x)
		{
			drawSegment(_grid.gridToWorldCoordinate(v1));
			++v1.x;
		}
	}
	else if (v1.y != v2.y)
	{
		++v1.y;

		while (v1.y <= v2.y)
		{
			drawSegment(_grid.gridToWorldCoordinate(v1));
			++v1.y;
		}
	}
	else if (v1.z != v2.z)
	{
		++v1.z;

		while (v1.z <= v2.z)
		{
			drawSegment(_grid.gridToWorldCoordinate(v1));
			++v1.z;
		}
	}
}

void Snake::drawSegment(gmt::vec3 position)
{
	
	position -= _grid.getOrigin();
	float_t size = _grid.getCubeSize();
	float_t hSize = size * 0.5f;

	float_t lx = std::max(position.x - hSize, 0.0f);
	float_t rx = std::min(position.x + hSize, _grid.getWidth() * size);
	float_t ly = std::max(position.y - hSize, 0.0f);
	float_t ry = std::min(position.y + hSize, _grid.getHeight() * size);
	float_t lz = std::max(position.z - hSize, 0.0f);
	float_t rz = std::min(position.z + hSize, _grid.getLength() * size);

	float_t mx = (lx + rx) * 0.5f;
	float_t my = (ly + ry) * 0.5f;
	float_t mz = (lz + rz) * 0.5f;

	position = gmt::vec3{ mx, my, mz } + _grid.getOrigin();

	_segment.setPosition(position);
	_segment.resize({ rx - lx, ry - ly, rz - lz });
	_segment.draw(_projection, _view);
}

std::vector<gmt::vec3> Snake::createDirVectors()
{
	std::vector<gmt::vec3> dirVectors(6);

	dirVectors[NORTH] = {0.0f, 0.0f, -1.0f};
	dirVectors[EAST] = { 1.0f, 0.0f, 0.0f };
	dirVectors[SOUTH] = { 0.0f, 0.0f, 1.0f };
	dirVectors[WEST] = { -1.0f, 0.0f, 0.0f };
	dirVectors[UP] = { 0.0f, 1.0f, 0.0f };
	dirVectors[DOWN] = { 0.0f, -1.0f, 0.0f };

	return move(dirVectors);
}

DIRECTION Snake::deduceDirection(const gmt::vec3& v)
{
	if (v.x != 0.0f)
		return v.x > 0.0f ? DIRECTION::EAST : DIRECTION::WEST;
	else if (v.y != 0.0f)
		return v.y > 0.0f ? DIRECTION::UP : DIRECTION::DOWN;

	return v.z > 0.0f ? DIRECTION::SOUTH : DIRECTION::NORTH;
}

float_t Snake::goToTarget(float_t canTravel)
{
	gmt::vec3 head = _chains.front().front();
	gmt::vec3 tail = _chains.back().back();
	gmt::vec3 target = _grid.gridToWorldCoordinate(_target);
	gmt::vec3i wasGridHead = toBlockPosition(head);

	float_t distanceToTarget = gmt::distance(head, target);
	float_t travelled = std::min(distanceToTarget, canTravel);

	head = moveInDirection(head, deduceDirection(target - head), travelled);

	_chains.front().front() = head;

	gmt::vec3i newGridHead = toBlockPosition(head);

	if (wasGridHead != newGridHead && _currentPositions.find(newGridHead) != _currentPositions.end())
	{
		_collided = true;
		std::cerr << "Collision!!!!" << std::endl;
	}

	_currentPositions.erase(_currentPositions.find(wasGridHead));
	_currentPositions.insert(newGridHead);

	if (travelled == distanceToTarget)
	{
		_chains.front().push_front(target);
		_currentPositions.insert(newGridHead);
		changeTarget();
	}

	moveTail(travelled);
		
	return canTravel - travelled;
}

gmt::vec3 Snake::moveInDirection(const gmt::vec3 &v, DIRECTION direction, float_t distance)
{
	return v + dirVectors[direction] * distance;
}

void Snake::moveTail(float_t distanceTravelled)
{
	static bool wasPopped = false;

	while (distanceTravelled > 0.0f)
	{
		while (_chains.back().size() >= 2 && distanceTravelled > 0.0f)
		{
			gmt::vec3 tail = _chains.back().back();
			gmt::vec3 beforeTail = _chains.back()[_chains.back().size() - 2];
			float_t distance = gmt::distance(tail, beforeTail);

			if (wasPopped)
			{
				_currentPositions.erase(_currentPositions.find(toBlockPosition(_chains.back().back())));
				_chains.back().pop_back();
				wasPopped = false;
				continue;
			}

			if (distance > distanceTravelled)
			{
				_currentPositions.erase(_currentPositions.find(toBlockPosition(_chains.back().back())));
				_chains.back().back() = moveInDirection(tail, deduceDirection(beforeTail - tail), distanceTravelled);
				_currentPositions.insert(toBlockPosition(_chains.back().back()));
				return;
			}
			else
			{
				distanceTravelled -= distance;
				_currentPositions.erase(_currentPositions.find(toBlockPosition(_chains.back().back())));
				_chains.back().pop_back();
			}
		}

		if (distanceTravelled <= 0.0f)
			return;

		if (!_chains.empty())
		{
			wasPopped = true;
			_currentPositions.erase(_currentPositions.find(toBlockPosition(_chains.back().back())));
			_chains.pop_back();
		}
	}
}

void Snake::changeTarget()
{
	gmt::vec3 targetWorld = _grid.gridToWorldCoordinate(_target);
	gmt::vec3i newTarget = _grid.worldToGridCoordinate(moveInDirection(targetWorld, _direction, _grid.getCubeSize()));

	if (_grid.isInside(newTarget))
	{
		_target = newTarget;
		return;
	}

	if (_target.x != newTarget.x)
		newTarget.x = _grid.getWidth() - 1 - _target.x;
	else if (_target.y != newTarget.y)
		newTarget.y = _grid.getHeight() - 1 - _target.y;
	else
		newTarget.z = _grid.getLength() - 1 - _target.z;

	_target = newTarget;

	gmt::vec3 newPosition = moveInDirection(_grid.gridToWorldCoordinate(newTarget), 
											opposite(_direction), 
											_grid.getCubeSize());

	gmt::vec3 chainEnd = moveInDirection(targetWorld, _direction, _grid.getCubeSize());

	if (_currentPositions.find(toBlockPosition(newPosition)) != _currentPositions.end())
		_collided = true;


	_currentPositions.insert(toBlockPosition(chainEnd));
	_currentPositions.insert(toBlockPosition(newPosition));
	_currentPositions.insert(toBlockPosition(newPosition));

	_chains.front().push_front(chainEnd);
	_chains.push_front({ newPosition, newPosition });
}

DIRECTION Snake::opposite(DIRECTION direction)
{
	switch (direction)
	{
	case NORTH:
		return SOUTH;
	case EAST:
		return WEST;
	case SOUTH:
		return NORTH;
	case WEST:
		return EAST;
	case UP:
		return DOWN;
	case DOWN:
		return UP;
	default:
		return UP;
	}
}

gmt::vec3i Snake::toBlockPosition(const gmt::vec3& position)
{
	return _grid.worldToGridCoordinate(position + gmt::vec3(_grid.getCubeSize() * 0.5f));
}