#include "RigidBody.h"


#include "Entity.h"
#include "Transform.h"
#include "Core.h"
#include <iostream>
#include "SphereCollider.h"
#include "firstengine//Exception.h"
namespace firstengine
{
	void RigidBody::onInitialize()
	{
		position = getEntity()->getComponent<Transform>()->getPosition();
		velocity = glm::vec3(0.0f);
		mass = 1.0f;
		forceDueToGravity = -9.8f * mass;
		dragForce = 0.0;
		netForce = glm::vec3(0.0f, forceDueToGravity, 0.0f);
		physicsObject = std::make_shared<PE::GameObject>(getEntity()->getComponent<Transform>()->getPosition(), getEntity()->getComponent<Transform>()->getRotate());
		physicsObject->SetMass(mass);
		physicsObject->SetNetForce(netForce);
		physicsObject->SetVelocity(velocity);

		collider = std::make_shared<SphereCollider>();
	}

	void RigidBody::onAfterTick()
	{
		if (!isKinematic)
		{
			physicsTick();
		}

		collisionTick();
	}

	void RigidBody::physicsTick()
	{
		float deltaT = getCore()->getDeltaTime();
		if (deltaT == 0) { deltaT += 0.01; }
		calculateGravityWithDrag(deltaT);
		getEntity()->getComponent<Transform>()->setPosition(position);
	}

	void RigidBody::collisionTick()
	{
		std::shared_ptr<RigidBody> cmpRigidBody;
		for (int i = 0; i < getCore()->entities.size(); i++)
		{
			if(!(getCore()->entities.at(i) == getEntity()))
			{
				try
				{
					cmpRigidBody = getCore()->entities.at(i)->getComponent<RigidBody>();
				}
				catch (firstengine::Exception & e)
				{
					//std::cout << e.what() << std::endl;
					continue;

				}
				glm::vec3 contactPoint;
				bool collision;
			PE:CollisionDetection::SphereToSphere(physicsObject, cmpRigidBody->getPhysicsObject(), contactPoint, collision);
				if (collision)
				{
					for (size_t ci = 0; ci < getEntity()->components.size(); ci++)
					{
						getEntity()->components.at(ci)->onCollision(cmpRigidBody->getEntity());
					}
					i = getCore()->entities.size() + 1;
				}
			}

		}
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
			//std::cout << position.y << std::endl;
			netForce.y = static_cast<float>((forceDueToGravity + force));
			if (netForce.y > 0.0)
				netForce.y = 0.0f;
		}
		physicsObject->GetPosition(position);
	}

	void RigidBody::setCollider(std::shared_ptr <Collider> _collider)
	{
		collider = _collider;
	}


	void RigidBody::setScale(float x, float y, float z)
	{
		collider->setScale(x, y, z);
		physicsObject->SetScale(collider->getScale());

	}

	void RigidBody::setScale(float radius)
	{
		collider->setScale(radius);
		physicsObject->SetScale(collider->getScale());
	}
}