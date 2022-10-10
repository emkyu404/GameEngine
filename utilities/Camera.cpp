#include "Camera.h"

using namespace glm;

// Code inspired by https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/camera.h

Camera::Camera(float _posX, float _posY, float _posZ) {
	front = Vector3D(0.0f, 0.0f, -1.0f);
	movementSpeed = SPEED;
	mouseSensitivity = SENSITIVITY;
	zoom = ZOOM;
	position = Vector3D(_posX, _posY, _posZ);
	worldUp = Vector3D(0.0f, 1.0f, 0.0f); // hard code up is y axis
	yaw = YAW;
	pitch = PITCH;
	lock = false;
	updateCameraVectors();
}

mat4 Camera::getViewMatrix() {
	// Conversion from our Vector3D class to vec3 class of glm library
	vec3 glmPosition, glmFront, glmUp;
	glmPosition = vec3(this->position.getX(), this->position.getY(), this->position.getZ());
	glmFront = vec3(this->front.getX(), this->front.getY(), this->front.getZ());
	glmUp = vec3(this->up.getX(), this->up.getY(), this->up.getZ());
	return lookAt(glmPosition, glmPosition+glmFront, glmUp);
}

void Camera::processKeyboard(CameraMovement _direction, float _deltaTime) {
	if (lock)
		return;

	float velocity = movementSpeed * _deltaTime;
	
	if (_direction == FORWARD) {
		position = position + (front * velocity);
	}
	if (_direction == BACKWARD) {
		position = position - (front * velocity);
	}
	if (_direction == LEFT) {
		position = position - (right * velocity);
	}
	if (_direction == RIGHT) {
		position = position + (right * velocity);
	}
}

void Camera::processMouseMovement(float _xOffset, float _yOffset, GLboolean _constrainPitch) {
	if (lock)
		return;

	_xOffset *= mouseSensitivity;
	_yOffset *= mouseSensitivity;

	yaw += _xOffset;
	pitch += _yOffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (_constrainPitch)
	{
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
	}

	// update Front, Right and Up Vectors using the updated Euler angles
	updateCameraVectors();
}

void Camera::processMouseScroll(float _yOffset) {
	if (lock)
		return;

	zoom -= (float)_yOffset;
	if (zoom < 1.0f)
		zoom = 1.0f;
	if (zoom > 45.0f)
		zoom = 45.0f;
}

void Camera::updateCameraVectors() {
	// calculate the new Front vector
	Vector3D newfront;
	newfront.setX(cos(radians(yaw)) * cos(radians(pitch)));
	newfront.setY(sin(radians(pitch)));
	newfront.setZ(sin(radians(yaw)) * cos(radians(pitch)));
	front = newfront.normalize();
	// also re-calculate the Right and Up vector
	right = front.cross(worldUp).normalize(); // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	up = right.cross(front).normalize();
}

void Camera::setLock(bool _lockState) {
	lock = _lockState;
}

bool Camera::getLock()
{
	return lock;
}

float Camera::getZoom()
{
	return this->zoom;
}
