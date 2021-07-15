#include "snake.h"
#include <algorithm>
#include <iostream>
#include "settings.h"

Snake::Snake(const Grid& grid)
	: Snake(grid, Settings::getSnakeTailPos(), Settings::getSnakeHeadPos(), Settings::getSnakeSpeed(),
	  Settings::getSnakeColor()) 
{}

Snake::Snake(const Grid& grid, const gmt::vec3i& tailPos, const gmt::vec3i& headPos, sk_float speed, const gmt::vec3& color)
	: _grid(grid), _speed(speed), _color(color), _segment(gmt::vec3(grid.getCellSize()), {}, color)
{
	gmt::vec3i currentPos = headPos;

	while (currentPos != tailPos)
	{
		_segments.push_back(currentPos);

		currentPos += gmt::vec3i{currentPos.x != tailPos.x, currentPos.y != tailPos.y, currentPos.z != tailPos.z} *
					  (currentPos < tailPos ? 1 : -1);
	}

	_segments.push_back(currentPos);

	_nextDir = deduceDir(headPos - tailPos);
	_directions = std::deque<DIRECTION>(_segments.size(), _nextDir);
}

void Snake::draw(const gmt::mat4& projection, const gmt::mat4& view)
{
	for (sk_uint i = 0; i < _segments.size(); ++i)
	{
		if (!i)
			drawCubeSlice(_segments[i], _directions.front(), _headFill, projection, view);
		else if (i + 1 == _segments.size())
			drawCubeSlice(_segments[i], oppositeDir(_directions.back()), _tailFill, projection, view);
		else
			drawCube(_segments[i], projection, view);	
	}
}

void Snake::update(sk_double dt) 
{
	sk_float canAdd = _speed * dt;

	for (sk_uint i = 0; i < 2; ++i)
	{
		sk_float left = (1.0f - _headFill) * _grid.getCellSize();
		sk_float add = std::min(canAdd, left);

		canAdd -= add;

		if (add == left)
		{
			_segments.push_front(nextPos(_segments.front(), _nextDir));
			_segmentsSet.insert(_segments.front());

			if(!_directions.empty())
				_directions.front() = _nextDir;

			_directions.push_front(_nextDir);

			_headFill = 0.0f;
		}
		else
		{
			_headFill = std::min(1.0f, _headFill + add / _grid.getCellSize());
			break;
		}
	}

	canAdd = _speed * dt;

	sk_float growment = std::min({ _needsToGrow, _growSpeed * (sk_float)dt, canAdd });
	canAdd = std::max(0.0f, canAdd - growment);
	_needsToGrow = std::max(0.0f, _needsToGrow - growment);

	for (sk_uint i = 0; i < 2; ++i)
	{
		sk_float left = _tailFill * _grid.getCellSize();
		sk_float add = std::min(canAdd, left);

		canAdd -= add;

		if (add == left)
		{
			_segmentsSet.erase(_segments.back());
			_segments.pop_back();
			_directions.pop_back();

			_tailFill = 1.0f;
		}
		else
		{
			_tailFill = std::max(0.0f, _tailFill - add / _grid.getCellSize());
			break;
		}
	}
}

void Snake::grow(sk_float dLength)
{
	_needsToGrow += dLength;
}

void Snake::setDirection(DIRECTION dir)
{
	if(dir != oppositeDir(_directions.front()))
		_nextDir = dir;
}

bool Snake::occupyes(gmt::vec3i pos) const
{
	return _segmentsSet.find(pos) != _segmentsSet.end();
}

sk_uint Snake::occupyedCount(gmt::vec3i pos) const
{
	return _segmentsSet.count(pos);
}

gmt::vec3i Snake::getHeadPos() const
{
	if (_segments.size() == 1 || _headFill != 0.0f)
		return _segments.front();

	return _segments[1];
}

gmt::vec3i Snake::getTailPos() const
{
	if(_segments.size() == 1 || _tailFill != 0.0f)
		return _segments.back();

	return _segments[_segments.size() - 2];
}

gmt::vec3 Snake::getWorldHeadPos() const
{
	return _grid.convertGridPos(getHeadPos());
}

gmt::vec3 Snake::getWorldTailPos() const
{
	return _grid.convertGridPos(getTailPos());
}

void Snake::drawCube(const gmt::vec3i& pos, const gmt::mat4& projection, const gmt::mat4& view)
{
	_segment.setPos(_grid.convertGridPos(pos));
	_segment.draw(projection, view);
}

void Snake::drawCubeSlice(const gmt::vec3i& pos, DIRECTION sliceDir, sk_float fill,
						  const gmt::mat4& projection, const gmt::mat4& view)
{
	gmt::vec3 delta = gmt::vec3(deduceVec(sliceDir)) * _grid.getCellSize() * (1.0f - fill);

	_segment.setPos(_grid.convertGridPos(pos) - delta * 0.5f);
	_segment.setSize(gmt::vec3(_grid.getCellSize()) - gmt::abs(delta));

	_segment.draw(projection, view);

	_segment.setSize(gmt::vec3(_grid.getCellSize()));
}

gmt::vec3i Snake::nextPos(gmt::vec3i pos, DIRECTION dir)
{
	pos += deduceVec(dir);
	pos.x = gmt::mod(pos.x, _grid.getWidth());
	pos.y = gmt::mod(pos.y, _grid.getHeight());
	pos.z = gmt::mod(pos.z, _grid.getLength());

	return pos;
}