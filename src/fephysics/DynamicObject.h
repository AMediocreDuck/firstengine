#include "glm/geometric.hpp"// glm::cross, glm::normalize 
#include "glm/glm.hpp"
class DynamicObject
{
private:
	glm::vec3 position;
	glm::vec3 rotation;

	float mass;

	glm::vec3 netForce;
	glm::vec3 velocity;

	bool isKinematic;
	bool useGravity;



public:
	DynamicObject();
	~DynamicObject();
	void GetMass(float& o_Mass);
	void GetNetForce(glm::vec3& o_NetForce);
	void GetPosition(glm::vec3& o_Position);
	void GetRotation(glm::vec3& o_Rotation);
	void GetVelocity(glm::vec3& o_Velocity);
	void GetKinematic(bool& o_Kinematic);
	void GetUseGravity(bool& o_Gravity);

	void SetMass(const float& i_Mass);
	void SetNetForce(const glm::vec3& i_NetForce);
	void SetPosition(const glm::vec3& i_Position);
	void SetRotation(const glm::vec3& i_Rotation);
	void SetVelocity(const glm::vec3& i_Velocity);
	void SetKinematic(const bool& i_Kinematic);
	void SetUseGravity(const bool& i_Gravity);

	void Euler(const float& i_DeltaT);
	void RK2(const float& i_DeltaT);
	void RK4(const float&i_DeltaT);

};
