#include "GameObject.h" 
namespace PE
{
	GameObject::GameObject()
	{
		SetPosition(glm::vec3(0.0f));
		SetRotation(glm::vec3(0.0f));


	}

	GameObject::GameObject(const glm::vec3& i_Position, const glm::vec3& i_Rotation)
	{
		SetPosition(i_Position);
		SetRotation(i_Rotation);

	}

	GameObject::~GameObject()
	{

	}

	void GameObject::SetPosition(const glm::vec3& i_Position)
	{
		position = i_Position;
	}

	void GameObject::SetRotation(const glm::vec3& i_Rotation)
	{
		rotation = i_Rotation;
	}

	void GameObject::SetScale(const glm::vec3& i_Scale)
	{
		scale = i_Scale;
	}
	
	void GameObject::SetVelocity(const glm::vec3& i_Velocity)
	{
		velocity = i_Velocity;
	}

	void GameObject::SetNetForce(const glm::vec3& i_NetForce)
	{
		netForce = i_NetForce;
	}

	void GameObject::SetMass(const float& i_Mass)
	{
		mass = i_Mass;
	}


	void GameObject::GetPosition(glm::vec3& o_Position)
	{
		o_Position = position;
	}

	void GameObject::GetRotation(glm::vec3& o_Rotation)
	{
		o_Rotation = rotation;
	}

	void GameObject::GetScale(glm::vec3& o_Scale)
	{
		o_Scale = scale;
	}

	void GameObject::GetVelocity(glm::vec3& o_Velocity)
	{
		o_Velocity = velocity;
	}

	void GameObject::GetNetForce(glm::vec3& o_NetForce)
	{
		o_NetForce = netForce;
	}

	void GameObject::Euler(const float& i_DeltaT)
	{
		glm::vec3 accerleration(0.0f);
		accerleration = (netForce / mass);
		position += (velocity * i_DeltaT);
		velocity += (accerleration * i_DeltaT);
	}

	void GameObject::RK2(const float& i_DeltaT) {
		glm::vec3 force(0.0f);
		glm::vec3 acceleration(0.0f);
		glm::vec3 k0(0.0f);
		glm::vec3 k1(0.0f);
		force = netForce;
		// Calculate k0 at t0. 
		acceleration = force / mass;
		k0 = i_DeltaT * acceleration;
		// Calculate k1 at t0 + deltaT/2 using k0/2.0f. 
		force = netForce + (k0 / 2.0f);
		acceleration = (force / mass);
		k1 = i_DeltaT * acceleration;
		position += (velocity * i_DeltaT);

		velocity += k1;
	}

	void GameObject::RK4(const float& i_DeltaT) {
		glm::vec3 force(0.0f);
		glm::vec3 acceleration(0.0f);
		glm::vec3 k0(0.0f);
		glm::vec3 k1(0.0f);
		glm::vec3 k2(0.0f);
		glm::vec3 k3(0.0f);
		// Calculate k0 at t0. 
		acceleration = netForce / mass;
		k0 = i_DeltaT * acceleration;
		// Calculate k1 at t0 + deltaT/2 using k0. 
		force = netForce + (k0 / 2.0f);
		acceleration = force / mass;
		k1 = i_DeltaT * acceleration;
		// Calculate k2 at t0 + deltaT/2 using k1. 
		force = netForce + k1;
		acceleration = force / mass;
		k2 = i_DeltaT * acceleration;
		// Calculate k3 at t0 + deltaT/2 using k2. 
		force = netForce + k2;
		acceleration = force / mass;
		k3 = i_DeltaT * acceleration;
		position += (velocity * i_DeltaT);
		velocity += (k0 + 2.0f * k1 + 2.0f * k2 + k3) / 6.0f;
	}
}


