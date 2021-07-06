#ifndef CAMERA_H
#define CAMERA_H
#include "gmath.h"
#include "skTypes.h"

class Camera
{
public:
	Camera(const gmt::vec3& target, sk_float radius, sk_float sensitivity = 0.01f, sk_float fov = gmt::radians(45.0f), 
		   sk_float pitch = 0.0f, sk_float yaw = 0.0f, const gmt::vec3& worldUp = {0.0f, 1.0f, 0.0f});

	void changePitch(sk_float deltaPitch);
	void changeYaw(sk_float deltaYaw);
	void setFov(sk_float fov);
	void zoom(sk_float delta);

	gmt::mat4 getViewMatrix() const;
	sk_float getSensitivity() const;
	sk_float getFov() const;
private:
	void recalculateSystem();

	const sk_float _sensitivity;
	const gmt::vec3 _worldUp;
	const sk_float _pitchUbound = gmt::radians(88.0f);
	const sk_float _pitchLbound = gmt::radians(-88.0f);
	const sk_float _fovUbound = gmt::radians(70.0f);
	const sk_float _fovLbound = gmt::radians(1.0f);
	const sk_float _zoomSpeed = 0.05f;

	gmt::vec3 _target;
	gmt::vec3 _spherePos;
	sk_float _radius;
	sk_float _pitch;
	sk_float _yaw;
	sk_float _fov;
	gmt::vec3 _front;
	gmt::vec3 _right;
	gmt::vec3 _up;
};

#endif

