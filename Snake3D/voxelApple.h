#ifndef VOXEL_APPLE_H
#define VOXEL_APPLE_H
#include "voxelSphere.h"

class VoxelApple : VoxelSphere 
{
public:
	explicit VoxelApple(const gmt::vec3& pos = gmt::vec3(0.0f),
			   sk_uint radius = 4,
			   sk_float sphereVoxelSize = 0.4f,
			   sk_float otherVoxelSize = 0.1f,
			   const gmt::vec3& sphereColor = gmt::vec3(0.0f),
			   const gmt::vec3& stickColor = gmt::vec3(0.0f),
			   const gmt::vec3& leavesColor = gmt::vec3(0.0f));

	void draw(const gmt::mat4& projection, const gmt::mat4& view) override;
	void update(sk_double deltaTime) override;

	void setPosition(const gmt::vec3& pos);
private:
	void drawCube(const gmt::vec3& pos, const gmt::mat4& projection, const gmt::mat4& view);

	Cube _cube;
	sk_float _otherVoxelSize;
	gmt::vec3 _sphereColor;
	gmt::vec3 _stickColor;
	gmt::vec3 _leavesColor;
};

#endif
