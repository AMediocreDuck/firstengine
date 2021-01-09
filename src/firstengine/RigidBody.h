#ifndef FIRSTENGINE_RIGIDBODY_H
#define FIRSTENGINE_RIGIDBODY_H

#include "fephysics/fephysics.h"
#include <glm/glm.hpp>
#include "Component.h"
#include <memory>

namespace firstengine
{
	class PE::GameObject;
	struct RigidBody : public Component
	{
		void onInitialize();
		void onAfterTick();
		void calculateOnlyGravity(float _deltaTime);
		void calculateGravityWithDrag(float _deltaTime);

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

		std::shared_ptr<PE::GameObject> physicsObject;
	};
}
#endif