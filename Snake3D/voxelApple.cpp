#include "voxelApple.h"

VoxelApple::VoxelApple(const gmt::vec3& pos,
					   sk_uint radius,
					   sk_float sphereVoxelSize,
					   sk_float otherVoxelSize,
					   const gmt::vec3& sphereColor,
					   const gmt::vec3& stickColor,
					   const gmt::vec3& leavesColor)
	: VoxelSphere(pos, radius, sphereVoxelSize, sphereColor), _cube(otherVoxelSize),
	  _otherVoxelSize(otherVoxelSize), _stickColor(stickColor), _leavesColor(leavesColor)
{}

void VoxelApple::draw(const gmt::mat4& projection, const gmt::mat4& view) 
{
	VoxelSphere::draw(projection, view);

	gmt::vec3 pos = VoxelSphere::getPosition();
	sk_float sphereVoxelSize = VoxelSphere::getVoxelSize();
	sk_uint radius = VoxelSphere::getRadius();

	gmt::vec3 upPos = pos + gmt::vec3{ 0.0f, sphereVoxelSize, 0.0f } * (radius + 0.5f);
	gmt::vec3 curPos = upPos + gmt::vec3(0.0f, 0.5f * _otherVoxelSize, 0.0f);

	_cube.setColor({ _stickColor.x, _stickColor.y, _stickColor.z, 1.0f });

	for (sk_uint i = 0; i < 4; ++i, curPos.y += _otherVoxelSize)
		drawCube(curPos, projection, view);

	_cube.setColor({ _leavesColor.x, _leavesColor.y, _leavesColor.z, 1.0f });
	
	upPos.y += 0.5f * _otherVoxelSize;

	drawCube(upPos + gmt::vec3{ 1.0f, -1.0f, 0.0f } * _otherVoxelSize, projection, view);
	drawCube(upPos + gmt::vec3{ 1.0f, 0.0f, 0.0f } *_otherVoxelSize, projection, view);
	drawCube(upPos + gmt::vec3{ 1.0f, 1.0f, 0.0f } *_otherVoxelSize, projection, view);
	drawCube(upPos + gmt::vec3{ 1.0f, 2.0f, 0.0f } *_otherVoxelSize, projection, view);
	drawCube(upPos + gmt::vec3{ 1.0f, 3.0f, 0.0f } *_otherVoxelSize, projection, view);
	drawCube(upPos + gmt::vec3{ 1.0f, 4.0f, 0.0f } *_otherVoxelSize, projection, view);

	drawCube(upPos + gmt::vec3{ 2.0f, 0.0f, 0.0f } *_otherVoxelSize, projection, view);
	drawCube(upPos + gmt::vec3{ 2.0f, 1.0f, 0.0f } *_otherVoxelSize, projection, view);
	drawCube(upPos + gmt::vec3{ 2.0f, 2.0f, 0.0f } *_otherVoxelSize, projection, view);
	drawCube(upPos + gmt::vec3{ 2.0f, 3.0f, 0.0f } *_otherVoxelSize, projection, view);
	drawCube(upPos + gmt::vec3{ 2.0f, 4.0f, 0.0f } *_otherVoxelSize, projection, view);
	drawCube(upPos + gmt::vec3{ 2.0f, 5.0f, 0.0f } *_otherVoxelSize, projection, view);

	drawCube(upPos + gmt::vec3{ 3.0f, 1.0f, 0.0f } *_otherVoxelSize, projection, view);
	drawCube(upPos + gmt::vec3{ 3.0f, 2.0f, 0.0f } *_otherVoxelSize, projection, view);
	drawCube(upPos + gmt::vec3{ 3.0f, 3.0f, 0.0f } *_otherVoxelSize, projection, view);
}

void VoxelApple::update(sk_double deltaTime) {}

void VoxelApple::drawCube(const gmt::vec3& pos, const gmt::mat4& projection, const gmt::mat4& view)
{
	_cube.setPosition(pos);
	_cube.draw(projection, view);
}