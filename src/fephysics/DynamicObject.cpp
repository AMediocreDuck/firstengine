#include "DynamicObject.h" 
DynamicObject::DynamicObject() 
{
	mass = 1.0f;
	netForce = glm::vec3(0.0, 0.0, 0.0);
	position = glm::vec3(0.0, 0.0, 0.0);
	rotation = glm::vec3(0.0, 0.0, 0.0);

	isKinematic = false;
	useGravity = true;

}

DynamicObject::~DynamicObject()
{ }

void DynamicObject::GetMass(float& o_Mass) 
{

	o_Mass = mass;
}

void DynamicObject::GetNetForce(glm::vec3& o_NetForce)
{

	o_NetForce = netForce;
}

void DynamicObject::GetPosition(glm::vec3& o_Position) 
{

	o_Position = position;
}
void DynamicObject::GetRotation(glm::vec3& o_Rotation)
{

	o_Rotation = rotation;
}

void DynamicObject::GetVelocity(glm::vec3 & o_Velocity)
{
	o_Velocity = velocity;
}

void DynamicObject::GetKinematic(bool& o_Kinematic)
{
	o_Kinematic = isKinematic;
}

void DynamicObject::GetUseGravity(bool& o_Gravity)
{
	o_Gravity = useGravity;
}

void DynamicObject::SetMass(const float& i_Mass)
{
	mass = i_Mass;
}

void DynamicObject::SetNetForce(const glm::vec3& i_NetForce)
{
	netForce = i_NetForce;
}

void DynamicObject::SetPosition(const glm::vec3& i_Position)
{
	position = i_Position;
}

void DynamicObject::SetRotation(const glm::vec3& i_Rotation)
{
	rotation = i_Rotation;
}

void DynamicObject::SetVelocity(const glm::vec3 & i_Velocity)
{
	velocity = i_Velocity;
}

void DynamicObject::SetKinematic(const bool& i_Kinematic)
{
	isKinematic = i_Kinematic;
}

void DynamicObject::SetUseGravity(const bool& i_Gravity)
{
	useGravity = i_Gravity;
}

void DynamicObject::Euler(const float& i_DeltaT)
{
	glm::vec3 accerleration;
	accerleration = (netForce / mass);
	position += (velocity * i_DeltaT);
	velocity += (accerleration * i_DeltaT);
}

void DynamicObject::RK2(const float & i_DeltaT) {
	glm::vec3 force;
	glm::vec3 acceleration;
	glm::vec3 k0;
	glm::vec3 k1;
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

void DynamicObject::RK4(const float & i_DeltaT) {
	glm::vec3 force;
	glm::vec3 acceleration;
	glm::vec3 k0;
	glm::vec3 k1;
	glm::vec3 k2;
	glm::vec3 k3;
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

