#include "camera.h"
#include <algorithm>
#include "settings.h"

Camera::Camera()
	:_target(Settings::getCameraTarget()), _radius(Settings::getCameraRadius()),
	 _sensitivity(Settings::getCameraSensitivity()), _pitch(Settings::getCameraPitch()), 
	 _yaw(Settings::getCameraYaw()), _fov(Settings::getFov()), _worldUp(Settings::getWorldUp())
{
	recalculateSystem();
}

Camera::Camera(const gmt::vec3& target, sk_float radius, sk_float sensitivity, sk_float fov, sk_float pitch, 
	           sk_float yaw, const gmt::vec3& worldUp)
	:_target(target), _radius(radius), _sensitivity(sensitivity), 
	 _pitch(pitch), _yaw(yaw), _fov(fov), _worldUp(worldUp)
{
	recalculateSystem();
}

sk_float Camera::getSensitivity() const
{
	return _sensitivity;
}

gmt::mat4 Camera::getViewMatrix() const
{
	gmt::mat4 look({ {_right.x, _right.y, _right.z, 0.0f},
					 {_up.x, _up.y, _up.z, 0.0f },
					 {-_front.x, -_front.y, -_front.z, 0.0f},
					 {0.0f, 0.0f, 0.0f, 1.0f }});

	return gmt::translate(-_target) * look * gmt::translate(-_spherePos);
}

void Camera::changePitch(sk_float deltaPitch)
{
	_pitch += deltaPitch;

	_pitch = std::min(_pitch, _pitchUbound);
	_pitch = std::max(_pitch, _pitchLbound);

	recalculateSystem();
}

void Camera::changeYaw(sk_float deltaYaw)
{
	_yaw += deltaYaw;
	_yaw = std::fmod(_yaw, 2.0f * gmt::PI);

	recalculateSystem();
}

void Camera::recalculateSystem()
{
	gmt::vec3 fromCenter = gmt::normalize({ cos(_pitch) * sin(_yaw), sin(_pitch), -cos(_pitch) * cos(_yaw) });
	_spherePos = -fromCenter * _radius;

	_front = fromCenter;
	_right = gmt::normalize(gmt::cross(_front, _worldUp));
	_up = gmt::normalize(gmt::cross(_right, _front));
}

void Camera::setFov(sk_float fov)
{
	_fov = gmt::clamp(fov, _fovLbound, _fovUbound);
}

sk_float Camera::getFov() const
{
	return _fov;
}

void Camera::zoom(sk_float delta)
{
	_fov += delta * _zoomSpeed;
	_fov = gmt::clamp(_fov, _fovLbound, _fovUbound);
}