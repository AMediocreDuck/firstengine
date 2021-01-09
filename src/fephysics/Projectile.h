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
	class Projectile
	{
	public:
		void static TrajectoryGravityOnlyModel(std::shared_ptr<GameObject> io_GameObject, const glm::vec3& i_InitialVelocity, const glm::vec3& i_InitialPosition, const float& i_Time);
		void static TrajectoryDragForceOnly(GameObject& io_GameObject, const float& i_Time);
		void static TrajectoryDragAndWind(GameObject& io_GameObject, const glm::vec3& i_WindVelocity, const float& i_Time);
		void static TrajectoryDragWindAndSpin(GameObject& io_GameObject, const glm::vec3& i_WindVelocity, const float& i_Time);
	};
}
