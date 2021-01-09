#include "RigidBody.h"


#include "Entity.h"
#include "Transform.h"
#include "Core.h"
#include <iostream>

namespace firstengine
{
	void RigidBody::onInitialize()
	{
		velocity = glm::vec3(0.0f);
		mass = 1.0f;
		forceDueToGravity = -9.8f * mass;
		dragForce = 0.0;
		netForce = glm::vec3(0.0f, forceDueToGravity, 0.0f);
		physicsObject = std::make_shared<PE::GameObject>(getEntity()->getComponent<Transform>()->getPosition(), getEntity()->getComponent<Transform>()->getRotate());
		physicsObject->SetMass(mass);
		physicsObject->SetNetForce(netForce);
		physicsObject->SetVelocity(velocity);
	}

	void RigidBody::onAfterTick()
	{
		float deltaT = getCore()->getDeltaTime();
		if (deltaT == 0) { deltaT += 0.01; }
		calculateGravityWithDrag(deltaT);
		getEntity()->getComponent<Transform>()->setPosition(position);
	}

	void RigidBody::calculateOnlyGravity(float _deltaTime)
	{
		physicsObject->GetPosition(position);
		PE::Projectile::TrajectoryGravityOnlyModel(physicsObject, velocity, position , _deltaTime);
		physicsObject->GetPosition(position);
		physicsObject->GetVelocity(velocity);
	}

	void RigidBody::calculateGravityWithDrag(float _deltaTime)
	{
		double force = dragForce;
		double dragCoefficient = 0.7;
		double airDensity = 1.2;
		double crossSectionArea = 0.18;

		physicsObject->SetVelocity(velocity);
		physicsObject->SetNetForce(netForce);
		physicsObject->SetPosition(position);
		physicsObject->Euler(_deltaTime);
		physicsObject->GetVelocity(velocity);
		if (dragForce < abs(forceDueToGravity))
		{
			PE::BasicNewtonianPhysics::ComputeDragForce(airDensity,
				(double)velocity.y, dragCoefficient, crossSectionArea, force);
			std::cout << velocity.y << std::endl;
			netForce.y = static_cast<float>((forceDueToGravity + force));
			if (netForce.y > 0.0)
				netForce.y = 0.0f;
		}
		physicsObject->GetPosition(position);
	}
}