#pragma once

#include <GLEW/glew.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include "Vector3D.hpp"
#include <vector>
using namespace glm;

// Code inspired by https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/camera.h

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;




enum CameraMovement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera
{
public :

	/* -- Constructors -- */

	Camera(float _posX, float _posY, float _posZ);

	/* -- Methods -- */
	mat4 getViewMatrix();
	void processKeyboard(CameraMovement _direction, float _deltaTime);
	void processMouseMovement(float _xOffset, float _yOffset, GLboolean _constrainPitch);
	void processMouseScroll(float _yOffset);
	void setMovementSpeed(float _moveSpeed); 
	void setLock(bool _lockState);
	bool getLock();
	float getZoom();

private:
	Vector3D position;
	Vector3D front;
	Vector3D up;
	Vector3D right;
	Vector3D worldUp;

	float yaw;
	float pitch;

	float movementSpeed;
	float mouseSensitivity;
	float zoom;

	bool lock;

	void updateCameraVectors();
};