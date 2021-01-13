#ifndef FIRSTENGINE_RIGIDBODY_H
#define FIRSTENGINE_RIGIDBODY_H

#include "fephysics/fephysics.h"
#include <glm/glm.hpp>
#include "Component.h"
#include <memory>

namespace firstengine
{
	class PE::GameObject;
	struct Collider;
	/********************************************//**
	* \brief Component to add Physics to an object
	***********************************************/
	struct RigidBody : public Component
	{
		/********************************************//**
		* \brief Function called during creation
		***********************************************/
		void onInitialize();
		/********************************************//**
		* \brief Ticks after all Entities have finished their tick()
		***********************************************/
		void onAfterTick();
		/********************************************//**
		* \brief All physic Calculations to be added into onAfterTick()
		***********************************************/
		void physicsTick();
		/********************************************//**
		* \brief All collision Calculations to be added into onAfterTick()
		***********************************************/
		void collisionTick();
		/********************************************//**
		* \brief Adds a constant gravity force
		***********************************************/
		void calculateOnlyGravity(float _deltaTime);
		/********************************************//**
		* \brief Adds a Gravity force that takes into account Drag
		***********************************************/
		void calculateGravityWithDrag(float _deltaTime);
		/********************************************//**
		* \brief Adds a Collider to the RigidBody
		***********************************************/
		void setCollider(std::shared_ptr<Collider> _collider);
		/********************************************//**
		* \brief Sets the Colliders Scale
		***********************************************/
		void setScale(float x, float y, float z);
		void setScale(float _radius);
		/********************************************//**
		* \brief Sets whether the RigidBody will apply physics or not
		* True = No Physics
		* False = Physics
		***********************************************/
		void setKinematic(bool _Kinematic) { isKinematic = _Kinematic; }
		/********************************************//**
		* \brief Returns pointer to the physics object
		***********************************************/
		std::shared_ptr<PE::GameObject> getPhysicsObject() { return physicsObject; }

	private:
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;

		glm::vec3 velocity;
		double mass;
		double forceDueToGravity;
		glm::vec3 netForce;
		double dragForce;

		bool isKinematic;
		bool gravityOn;

		std::shared_ptr<Collider> collider;
		std::shared_ptr<PE::GameObject> physicsObject;
	};
}
#endif