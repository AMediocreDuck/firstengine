#pragma once 
#define _USE_MATH_DEFINES 
#include <cmath> 
#include "glm/vec3.hpp"// glm::vec3 
#include "glm/geometric.hpp"// glm::cross, glm::normalize 
#include "GameObject.h" 
#include <iostream> 
#include <iomanip> 
#include <conio.h> 
#include <memory>

namespace PE
{
	class CollisionDetection
	{
	public:
		void static SphereToPointOnPlane(GameObject& i_GameObject, glm::vec3& i_PointOnPlane, glm::vec3& i_Normal, float& o_Distance, bool& o_collision);
		void static SphereToSphere(std::shared_ptr<GameObject> i_GameObjectA, std::shared_ptr<GameObject> i_GameObjectB, glm::vec3& o_ContactPoint, bool& o_Collision);
		void static SphereToSphereWithTime(GameObject& i_GameObjectA, GameObject& i_GameObjectB, glm::vec3& o_ContactPoint, double& o_Time, bool& o_Collision);
		void static AABB(GameObject& i_GameObjectA, GameObject& i_GameObjectB, bool& o_CollisionDetection);  	private:
		void static AABBCollisionXYZ(float i_MinA, float i_MaxA, float i_MinB, float i_MaxB, bool& o_Collision);
	};
}
