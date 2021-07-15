#include "voxelApple.h"

VoxelApple::VoxelApple(const gmt::vec3& pos, sk_uint radius, sk_float sphereVoxelSize, sk_float otherVoxelSize,
					   const gmt::vec3& sphereColor, const gmt::vec3& stickColor, const gmt::vec3& leavesColor)
	: VoxelSphere(pos, radius, sphereVoxelSize, sphereColor), _voxel(otherVoxelSize),_stickColor(stickColor), 
	  _leavesColor(leavesColor)
{}

void VoxelApple::draw(const gmt::mat4& projection, const gmt::mat4& view) const
{
	gmt::vec3 pos = VoxelSphere::getPos();
	sk_float sphereVoxelSize = VoxelSphere::getVoxelSize();
	sk_float otherVoxelSize = _voxel.getSize();
	sk_uint radius = VoxelSphere::getRadius();

	gmt::vec3 upPos = pos + gmt::vec3{ 0.0f, sphereVoxelSize, 0.0f } * (radius + 0.5f);

	VoxelSphere::draw(projection, view);
	drawStick(upPos, otherVoxelSize, projection, view);
	drawLeaves(upPos, otherVoxelSize, projection, view);
}

void VoxelApple::setPos(const gmt::vec3& pos)
{
	VoxelSphere::setPos(pos);
}

gmt::vec3 VoxelApple::getPos() const
{
	return VoxelSphere::getPos();
}

void VoxelApple::drawStick(const gmt::vec3& upPos, float_t voxelSize, const gmt::mat4& projection, const gmt::mat4& view) const
{
	gmt::vec3 curPos = upPos + gmt::vec3(0.0f, 0.5f * voxelSize, 0.0f);

	_voxel.setColor(_stickColor);

	for (sk_uint i = 0; i < 4; ++i, curPos.y += voxelSize)
		drawCube(curPos, projection, view);
}

void VoxelApple::drawLeaves(gmt::vec3 upPos, float_t voxelSize, const gmt::mat4& projection, const gmt::mat4& view) const
{
	_voxel.setColor(_leavesColor);

	upPos.y += 0.5f * voxelSize;

	drawCube(upPos + gmt::vec3{ 1.0f, -1.0f, 0.0f } * voxelSize, projection, view);
	drawCube(upPos + gmt::vec3{ 1.0f, 0.0f, 0.0f } * voxelSize, projection, view);
	drawCube(upPos + gmt::vec3{ 1.0f, 1.0f, 0.0f } * voxelSize, projection, view);
	drawCube(upPos + gmt::vec3{ 1.0f, 2.0f, 0.0f } * voxelSize, projection, view);
	drawCube(upPos + gmt::vec3{ 1.0f, 3.0f, 0.0f } * voxelSize, projection, view);
	drawCube(upPos + gmt::vec3{ 1.0f, 4.0f, 0.0f } * voxelSize, projection, view);

	drawCube(upPos + gmt::vec3{ 2.0f, 0.0f, 0.0f } * voxelSize, projection, view);
	drawCube(upPos + gmt::vec3{ 2.0f, 1.0f, 0.0f } * voxelSize, projection, view);
	drawCube(upPos + gmt::vec3{ 2.0f, 2.0f, 0.0f } * voxelSize, projection, view);
	drawCube(upPos + gmt::vec3{ 2.0f, 3.0f, 0.0f } * voxelSize, projection, view);
	drawCube(upPos + gmt::vec3{ 2.0f, 4.0f, 0.0f } * voxelSize, projection, view);
	drawCube(upPos + gmt::vec3{ 2.0f, 5.0f, 0.0f } * voxelSize, projection, view);

	drawCube(upPos + gmt::vec3{ 3.0f, 1.0f, 0.0f } * voxelSize, projection, view);
	drawCube(upPos + gmt::vec3{ 3.0f, 2.0f, 0.0f } * voxelSize, projection, view);
	drawCube(upPos + gmt::vec3{ 3.0f, 3.0f, 0.0f } * voxelSize, projection, view);
}

void VoxelApple::drawCube(const gmt::vec3& pos, const gmt::mat4& projection, const gmt::mat4& view) const
{
	_voxel.setPos(pos);
	_voxel.draw(projection, view);
}