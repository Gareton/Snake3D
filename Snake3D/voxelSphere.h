#ifndef VOXEL_SPHERE_H
#define VOXEL_SPHERE_H
#include "drawable.h"
#include "gmath.h"
#include "skTypes.h"
#include "cube.h"

class VoxelSphere : Drawable 
{
public:
	explicit VoxelSphere(const gmt::vec3& pos = gmt::vec3(0.0f),
						 sk_uint radius = 4,
						 sk_float voxelSize = 0.4f,
						 const gmt::vec3& color = gmt::vec3(0.0f));

	void draw(const gmt::mat4& projection, const gmt::mat4& view) override;
	void update(sk_double deltaTime) override;
private:
	Cube _cube;
	const gmt::vec3 _pos;
	sk_uint _radius;
	sk_float _voxelSize;
};

#endif
