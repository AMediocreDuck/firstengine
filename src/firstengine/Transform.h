#ifndef FIRSTENGINE_TRANSFORM_H
#define FIRSTENGINE_TRANSFORM_H

#include <glm/glm.hpp>
#include "Component.h"

namespace firstengine
{
	/********************************************//**
	* \brief Transform holds all positional data
	***********************************************/
	struct Transform : public Component
	{
		/********************************************//**
		* \brief Called when transform is first created
		***********************************************/
		void onInitialize();
		/********************************************//**
		* \brief Returns the model matrix
		***********************************************/
		glm::mat4 getModelMat();
		/********************************************//**
		* \brief Returns the position of the Entity
		***********************************************/
		glm::vec3 getPosition() { return position; }
		/********************************************//**
		* \brief Returns the rotation of the Entity
		***********************************************/
		glm::vec3 getRotate() { return rotation; }
		/********************************************//**
		* \brief Moves the Entity based on the data inputted
		***********************************************/
		void translate(float x, float y, float z);
		/********************************************//**
		* \brief Sets the position to the inputted data
		***********************************************/
		void setPosition(glm::vec3 _position);
		/********************************************//**
		* \brief Sets the rotation to the inputted data
		***********************************************/
		void setRotation(glm::vec3 _rotation);
		/********************************************//**
		* \brief Sets the scale to the inputted data 
		***********************************************/
		void setScale(glm::vec3 _scale);

	private:
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
		glm::vec3 direction;
	};
}


#endif 
