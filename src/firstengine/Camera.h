#ifndef FIRSTENGINE_CAMERA_H
#define FIRSTENGINE_CAMERA_H

#include "Component.h"
#include <glm/glm.hpp> //glm::mat4
#include <memory>


namespace firstengine
{
	/********************************************//**
	* \brief Camera Component: Used to determine which Entity has a Camera attached
	***********************************************/
	struct Camera : public Component
	{
		/********************************************//**
		* \brief Sets up the Camera and adds itself to the list of cameras
		***********************************************/
		void onInitialize();
		/********************************************//**
		* \brief Retunrs the cameras position from its Transform
		***********************************************/
		glm::vec3 getCameraPos();
		/********************************************//**
		* \brief Returns the vector that corrosponds to directly up from where the camera is looking
		***********************************************/
		//glm::vec3 getCameraUp() { return cameraUp; }
		/********************************************//**
		* \brief Returns the vector that corrosponds to the direction the camera is facing
		***********************************************/
		//glm::vec3 getCameraFront() { return cameraFront; }
		/********************************************//**
		* \brief Returns a view matrix based on the cameras position, rotation etc
		***********************************************/
		glm::mat4 getViewMatrix();

		/********************************************//**
		* \brief Sets how fast the camera will move
		***********************************************/
		//void setCameraSpeed(float _cameraSpeed, float _deltaTime) { cameraSpeed = _cameraSpeed * _deltaTime; }
		//float getCameraSpeed() { return cameraSpeed; }

	private:
		//glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		//glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		////float yaw = -90;
		////float pitch = 0;
		//int lastMouseX = 540;
		//int lastMouseY = 360;

		//float cameraSpeed;
	};
}

#endif

