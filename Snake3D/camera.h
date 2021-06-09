#ifndef CAMERA_H
#define CAMERA_H
#include "gmath.h"

class Camera
{
public:
	Camera(const gmt::vec3& target, float_t radius, float_t sensitivity = 0.01f, float_t fov = gmt::radians(45.0f), 
		float_t pitch = 0.0f, float_t yaw = 0.0f, const gmt::vec3& worldUp = {0.0f, 1.0f, 0.0f});

	void changePitch(float_t deltaPitch);
	void changeYaw(float_t deltaYaw);
	void setFov(float_t fov);
	void zoom(float_t delta);

	gmt::mat4 getViewMatrix();
	float_t getSensitivity();
	float_t getFov();
private:
	void recalculateSystem();

	const float_t _sensitivity;
	const gmt::vec3 _worldUp;
	gmt::vec3 _target;
	gmt::vec3 _spherePosition;
	float_t _radius;
	float_t _pitch;
	float_t _yaw;
	float_t _fov;
	gmt::vec3 _front;
	gmt::vec3 _right;
	gmt::vec3 _up;
	const float_t _pitchUbound = gmt::radians(88.0f);
	const float_t _pitchLbound = gmt::radians(-88.0f);
	const float_t _fovUbound = gmt::radians(70.0f);
	const float_t _fovLbound = gmt::radians(1.0f);
	const float_t _zoomSpeed = 0.05f;
};

#endif

