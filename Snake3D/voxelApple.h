#ifndef VOXEL_APPLE_H
#define VOXEL_APPLE_H
#include "voxelSphere.h"
#include "updatable.h"

class VoxelApple : public VoxelSphere,
				   public Updatable
{
public:
	explicit VoxelApple(const gmt::vec3& pos = gmt::vec3(0.0f), sk_uint radius = 4, sk_float sphereVoxelSize = 0.4f,
					    sk_float otherVoxelSize = 0.1f, const gmt::vec3& sphereColor = {1.0f, 0.0f, 0.0f},
						const gmt::vec3& stickColor = gmt::vec3(0.0f), const gmt::vec3& leavesColor = gmt::vec3(0.0f));

	void draw(const gmt::mat4& projection, const gmt::mat4& view) const override;
	void update(sk_double dt) override;

	void setPos(const gmt::vec3& pos);

	gmt::vec3 getPos() const;
private:
	void drawStick(const gmt::vec3& upPos, float_t voxelSize, const gmt::mat4& projection, const gmt::mat4& view) const;
	void drawLeaves(gmt::vec3 upPos, float_t voxelSize, const gmt::mat4& projection, const gmt::mat4& view) const;
	void drawCube(const gmt::vec3& gPos, const gmt::vec3& rPos, const gmt::mat4& projection, const gmt::mat4& view) const;

	mutable bge::Cube _voxel;

	gmt::vec3 _sphereColor;
	gmt::vec3 _stickColor;
	gmt::vec3 _leavesColor;

	gmt::mat4 _tform = gmt::mat4(1.0f);
	sk_double _passed = 0.0f;
	const sk_float _rotateSpeed = 1.0f;
	const sk_float _floatSpeed = 2.0f;
	const sk_float _floatRange = 0.2f;
};

#endif
