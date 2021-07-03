#include "voxelSphere.h"

VoxelSphere::VoxelSphere(const gmt::vec3& pos, sk_uint radius, sk_float voxelSize, const gmt::vec3& color)
	: _pos(pos), _radius(radius), _voxelSize(voxelSize), 
	_cube(voxelSize, gmt::vec3(0.0f), color)
{}

void VoxelSphere::draw(const gmt::mat4& projection, const gmt::mat4& view)
{
	sk_int intRadius = _radius;

	for (sk_int i = -intRadius; i <= intRadius; ++i)
		for (sk_int j = -intRadius; j <= intRadius; ++j)
			if (i * i + j * j <= gmt::sqr(intRadius))
				for(sk_int kSign = -1; kSign <= 1; kSign += 2)
					{
						sk_int k = std::floor(std::sqrt(gmt::sqr(intRadius) - i * i - j * j)) * kSign;

						gmt::vec3 voxelPos = gmt::vec3{ 1.0f * i, 1.0f * j, 1.0f * k } * _voxelSize;

						_cube.setPos(_pos + voxelPos);
						_cube.draw(projection, view);

						voxelPos = gmt::vec3{ 1.0f * k, 1.0f * j, 1.0f * i } *_voxelSize;

						_cube.setPos(_pos + voxelPos);
						_cube.draw(projection, view);

						voxelPos = gmt::vec3{ 1.0f * i, 1.0f * k, 1.0f * j } *_voxelSize;

						_cube.setPos(_pos + voxelPos);
						_cube.draw(projection, view);
					}
}

void VoxelSphere::setPosition(const gmt::vec3& pos)
{
	_pos = pos;
}

sk_uint VoxelSphere::getRadius()
{
	return _radius;
}

sk_float VoxelSphere::getVoxelSize()
{
	return _voxelSize;
}

gmt::vec3 VoxelSphere::getPosition()
{
	return _pos;
}