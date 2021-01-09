#pragma once
#include <glm/glm.hpp>
namespace PE
{
	class GameObject
	{
	private:
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;

		float mass;

		glm::vec3 netForce;
		glm::vec3 velocity;

		bool isKinematic;
		bool useGravity;
	public:
		GameObject();
		GameObject(const glm::vec3& i_Position, const glm::vec3& i_Rotation);
		~GameObject();

		void SetPosition(const glm::vec3& i_Position);
		void SetScale(const glm::vec3& i_Scale);
		void SetRotation(const glm::vec3& i_Rotation);
		void SetVelocity(const glm::vec3& i_Velocity);
		void SetNetForce(const glm::vec3& i_NetForce);
		void SetMass(const float& i_Mass);

		void GetPosition(glm::vec3& o_Position);
		void GetScale(glm::vec3& o_Scale);
		void GetRotation(glm::vec3& o_Rotation);
		void GetVelocity(glm::vec3& o_Velocity);
		void GetNetForce(glm::vec3& o_NetForce);

		void Euler(const float& i_DeltaT);
		void RK2(const float& i_DeltaT);
		void RK4(const float& i_DeltaT);

		//virtual void ProcessInput();
		//virtual void Update(const float& i_DeltaT);
		//virtual void Render();
	};
}
