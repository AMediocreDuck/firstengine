#ifndef FIRSTENGINE_CAMERA_H
#define FIRSTENGINE_CAMERA_H

#include "Component.h"
#include <glm/glm.hpp> //glm::mat4
#include <memory>


namespace firstengine
{

	struct Camera : public Component
	{
		/********************************************//**
		* \brief Sets up the Camera and adds itself to the list of cameras
		***********************************************/
		void onInitialize();
		/********************************************//**
		* \brief Sets the cameras different variables 
		***********************************************/
		void setCamera(glm::vec3 _cameraPos, int _width, int _height, float _yaw, float _pitch);
		/********************************************//**
		* \brief Updates the cameras direction and Up vector based on Mouse Movements
		***********************************************/
		//void setCameraDirection(float _mouseX, float _mouseY, float _xOffset, float _yOffset, float _mouseSensitivity);
		/********************************************//**
		* \brief Retunrs the cameras position from its Transform
		***********************************************/
		glm::vec3 getCameraPos();
		/********************************************//**
		* \brief Returns the vector that corrosponds to directly up from where the camera is looking
		***********************************************/
		glm::vec3 getCameraUp() { return cameraUp; }
		/********************************************//**
		* \brief Returns the vector that corrosponds to the direction the camera is facing
		***********************************************/
		glm::vec3 getCameraFront() { return cameraFront; }
		/********************************************//**
		* \brief Returns a view matrix based on the cameras position, rotation etc
		***********************************************/
		glm::mat4 getViewMatrix();

		/********************************************//**
		* \brief Sets how fast the camera will move
		***********************************************/
		void setCameraSpeed(float _cameraSpeed, float _deltaTime) { cameraSpeed = _cameraSpeed * _deltaTime; }
		float getCameraSpeed() { return cameraSpeed; }

	private:
		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		//float yaw = -90;
		//float pitch = 0;
		int lastMouseX = 540;
		int lastMouseY = 360;

		float cameraSpeed;
	};
}

#endif

