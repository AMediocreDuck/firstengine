#include "Camera.h"
#include "Entity.h"
#include "Transform.h"
#include "Core.h"
#include "Screen.h"

#include <glm/ext.hpp> 

namespace firstengine
{
	void Camera::onInitialize()
	{
		//getCore()->
		setCamera(glm::vec3(5.0f, 5.0f, 5.0f), getCore()->getScreen()->getWidth(), getCore()->getScreen()->getHeight(), -90.0f, 0.0f);
	}

	void Camera::setCamera(glm::vec3 _cameraPos, int _width, int _height, float _yaw, float _pitch)
	{
		getEntity()->getComponent<Transform>()->setPosition(_cameraPos);
		//cameraPos = _cameraPos;
		lastMouseX = _width / 2;
		lastMouseY = _height / 2;
		getEntity()->getComponent<Transform>()->setRotation(glm::vec3(0.0f,_pitch, _yaw));
		//yaw = _yaw;
		//pitch = _pitch;
	}

	//void Camera::setCameraDirection(float _mouseX, float _mouseY, float _xOffset, float _yOffset, float _mouseSensitivity)
	//{
	//	lastMouseX = _mouseX;
	//	lastMouseY = _mouseY;
	//	float xOffset = _xOffset * _mouseSensitivity;
	//	float yOffset = _yOffset * _mouseSensitivity;
	//	yaw += xOffset;
	//	pitch -= yOffset;
	//	if (pitch > 89.0f)
	//		pitch = 89.0f;
	//	if (pitch < -89.0f)
	//		pitch = -89.0f;

	//	glm::vec3 direction;
	//	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	//	direction.y = sin(glm::radians(pitch));
	//	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	//	cameraFront = glm::normalize(direction);

	//}

	glm::vec3 Camera::getCameraPos()
	{
		return getEntity()->getComponent<Transform>()->getPosition();
	}

	glm::mat4 Camera::getViewMatrix()
	{
		glm::mat4 view;
		view = glm::lookAt(getCameraPos(), getCameraPos() + cameraFront, cameraUp);
		return view;
	}

}
