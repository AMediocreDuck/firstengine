#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"// glm::vec4
#include "glm/glm.hpp"
#include "glm/geometric.hpp"// glm::cross, glm::normalize
namespace PE
{
	const double G = 0.0000000000667;
	const double g = 9.80;
	class BasicNewtonianPhysics
	{
	public:
		void static ComputeForceDueToGravity(const double& i_MassOne,
			const double& i_MassTwo, const double i_RadiusOne,
			const double& i_RadiusTwo, double& o_Acceleration);

		void static ComputeCentripetalAcceleration(const double& i_Velocity,
			const double& i_Radius, double& o_Acceleration);

		void static ComputeGravitationalPE(const double& i_H0,
			const double& i_Mass, double& o_PE);

		void static ComputeKineticEnergy(const double& i_Velocity, const double&
			i_Mass, double& o_KE);

		void static ComputeElasticPotentialEnergy(const double& i_SpringConstant, const double& i_AmountOfDisplacement,
			const double& o_ElesticPotentialEnergy);

		void static ComputeGravitationPotentialEnergy(const double& i_Mass, const double& i_Gravity, const double& i_Height,
			double& o_GravitationalPotentialEnergy);

		void static ComputeMechanicalEnergy(const double& i_GravitationalPotentialEnergy, const double& i_ElasticPotentialEnergy, const double& i_KineticEnergy,
			double& o_MechanicalEnergy);

		void static ComputeForce(const double& i_Mass, const double& i_Aceleration,
			double& o_Force);

		void static ComputeDragForce(const double& i_airDensity,const double& i_vely,
			const double& i_dragCoefficient, const double& i_crossSectionArea, double& o_force);

		void static FreeFallVelocityDueToGravity(const double& i_time, double& o_Velocity);

		void static FreeFallVelocityWithDrag(const double& i_time, const double& i_mass,
			const double& i_AirDensity, const double& i_DragCoefficient,
			const double& i_Area, double& o_TerminalVelocity);

		void static ComputeVerticalPosition(const double& i_time, const double& i_InitialHeight, const double& i_mass,
			const double& i_AirDensity, const double& i_DragCoefficient,
			const double& i_Area, double& o_VerticalPosition);


	private:
		void static ComputeTerminalVelocity(const double& i_mass,
			const double& i_AirDensity, const double& i_DragCoefficient,
			const double& i_Area, double& o_TerminalVelocity);


	};
}
