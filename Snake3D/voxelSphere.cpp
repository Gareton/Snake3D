#include "voxelSphere.h"

VoxelSphere::VoxelSphere(const gmt::vec3& pos, sk_uint radius, sk_float voxelSize, const gmt::vec3& color)
	: _pos(pos), _radius(radius), _voxelSize(voxelSize), 
	_cube(voxelSize, gmt::vec3(0.0f), gmt::vec4{ color.x, color.y, color.z, 1.0f })
{}

void VoxelSphere::draw(const gmt::mat4& projection, const gmt::mat4& view) 
{
	sk_int intRadius = _radius;

	for(sk_int i = -intRadius; i <= intRadius; ++i)
		for(sk_int j = -intRadius; j <= intRadius; ++j)
			for(sk_int k = -intRadius; k <= intRadius; ++k)
				if (i * i + j * j + k * k <= gmt::sqr(_radius))
				{
					gmt::vec3 voxelPos = gmt::vec3{ 1.0f * i, 1.0f * j, 1.0f * k } * _voxelSize;

					_cube.setPosition(voxelPos);
					_cube.draw(projection, view);
				}
}

void VoxelSphere::update(sk_double deltaTime) {}