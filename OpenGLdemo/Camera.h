#pragma once


#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Utils.h"

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	UPWARD,
	DOWNWARD,
	LEFT,
	RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:
	glm::vec3 _position;
	glm::vec3 _front;
	glm::vec3 _up;
	glm::vec3 _right;
	glm::vec3 _worldUp;

	float _yaw;
	float _pitch;

	float _movementSpeed;
	float _mouseSensitivity;
	float _zoom;

	Camera(glm::vec3 position = glm::vec3(0, 0, 0), glm::vec3 up = glm::vec3(0, 1, 0), float yaw = YAW, float pitch = PITCH, float zoom = ZOOM)
		:
		_front(glm::vec3(0, 0, -1)),
		_movementSpeed(SPEED)
	{
		_position = position;
		_worldUp = up;
		_yaw = yaw;
		_pitch = pitch;
		_zoom = zoom;
		_mouseSensitivity = SENSITIVITY;
		updateCameraVectors();
	}

	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(_position, _front + _position, _up);
	}

	void ProcessKeyboard(Camera_Movement direction, float deltaTime)
	{
		float velocity = _movementSpeed * deltaTime;

		if (direction == FORWARD)
			_position += _front * velocity;
		if (direction == BACKWARD)
			_position -= _front * velocity;
		if (direction == LEFT)
			_position -= _right * velocity;
		if (direction == RIGHT)
			_position += _right * velocity;
		if (direction == UPWARD)
			_position += _up * velocity;
		if (direction == DOWNWARD)
			_position -= _up * velocity;

	}

	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constraintPitch = true)
	{
		xoffset *= _mouseSensitivity;
		yoffset *= _mouseSensitivity;

		_yaw += xoffset;
		_pitch += yoffset;

		if (constraintPitch)
		{
			if (_pitch > 89.0f)
				_pitch = 89.0f;
			else if (_pitch < -89.0f)
				_pitch = -89.0f;
		}

		updateCameraVectors();
	}

	void ProcessMouseScroll(float xoffset, float yoffset)
	{
		_zoom += (xoffset - yoffset);
		_zoom = std::fmax(_zoom, 10.0f);
		_zoom = std::fmin(_zoom, 170.0f);
	}

	void Reset()
	{
		_yaw = YAW;
		_pitch = PITCH;
		_mouseSensitivity = SENSITIVITY;
		_movementSpeed = SPEED;
		_zoom = ZOOM;
		updateCameraVectors();
	}

private:
	void updateCameraVectors()
	{
		glm::vec3 direction;
		direction.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
		direction.y = sin(glm::radians(_pitch));
		direction.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
		_front = glm::normalize(direction);

		_right = glm::normalize(glm::cross(_front, _worldUp));
		_up = glm::normalize(glm::cross(_right, _front));
	}
};