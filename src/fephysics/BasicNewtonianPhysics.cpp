#include "BasicNewtonianPhysics.h"
void PE::BasicNewtonianPhysics::ComputeForceDueToGravity(const double&
	i_MassOne, const double& i_MassTwo,
	const double i_RadiusOne, const double& i_RadiusTwo, double& o_Acceleration)
{
	double radius = i_RadiusOne + i_RadiusTwo;
	o_Acceleration = ((G*i_MassOne*i_MassTwo) / (radius * radius));
	o_Acceleration = o_Acceleration / i_MassTwo;
}
void PE::BasicNewtonianPhysics::ComputeCentripetalAcceleration(const double&
	i_Velocity, const double& i_Radius, double& o_Acceleration)
{
	o_Acceleration = (i_Velocity * i_Velocity) / i_Radius;
}
void PE::BasicNewtonianPhysics::ComputeGravitationalPE(const double& i_H0,
	const double& i_Mass, double& o_PE)
{
	o_PE = i_H0 * i_Mass * g;
}
void static ComputeKineticEnergy(const double& i_Velocity, const double&
	i_Mass, double& o_KE)
{
	o_KE = (i_Mass * pow(i_Velocity, 2)) / 2;
}
void static ComputeElasticPotentialEnergy(const double& i_SpringConstant, const double& i_AmountOfDisplacement,
	 double& o_ElesticPotentialEnergy)
{
	o_ElesticPotentialEnergy = (i_SpringConstant * pow(i_AmountOfDisplacement, 2)) / 2;
}
void static ComputeGravitationPotentialEnergy(const double& i_Mass, const double& i_Gravity, const double& i_Height,
	double& o_GravitationalPotentialEnergy)
{
	o_GravitationalPotentialEnergy = i_Mass * i_Gravity * i_Height;
}
void static ComputeMechanicalEnergy(const double& i_GravitationalPotentialEnergy, const double& i_ElasticPotentialEnergy, const double& i_KineticEnergy,
	double& o_MechanicalEnergy)
{
	o_MechanicalEnergy = i_GravitationalPotentialEnergy + i_ElasticPotentialEnergy + i_KineticEnergy;
}

void PE::BasicNewtonianPhysics::ComputeForce(const double& i_Mass,
	const double& i_Aceleration, double& o_Force)
{
	o_Force = i_Mass * i_Aceleration;
}

void PE::BasicNewtonianPhysics::ComputeDragForce(const double & i_airDensity, const double & i_vely, const double & i_dragCoefficient, const double & i_crossSectionArea, double & o_force)
{
	double D = i_dragCoefficient * (0.5 * (i_airDensity * pow(i_vely, 2))) * i_crossSectionArea;
	o_force = D;
}

void PE::BasicNewtonianPhysics::FreeFallVelocityDueToGravity(const double& i_time,
	double& o_Velocity)
{
	o_Velocity = g * i_time;
}

void PE::BasicNewtonianPhysics::FreeFallVelocityWithDrag(const double& i_time,
	const double& i_mass, const double& i_AirDensity, const double& i_DragCoefficient,
	const double& i_Area, double& o_Velocity)
{
	double vel = 0.0; // terminal velocity
	PE::BasicNewtonianPhysics::ComputeTerminalVelocity(i_mass, i_AirDensity,
		i_DragCoefficient, i_Area, vel);
	o_Velocity = tanh((g * i_time) / vel);
	o_Velocity = -vel * o_Velocity;
}

void PE::BasicNewtonianPhysics::ComputeTerminalVelocity(const double& i_mass,
	const double& i_AirDensity, const double& i_DragCoefficient, const double& i_Area,
	double& o_TerminalVelocity)
{
	o_TerminalVelocity = sqrt((2 * g * i_mass) / (i_AirDensity *i_DragCoefficient *
		i_Area));
}

void PE::BasicNewtonianPhysics::ComputeVerticalPosition(const double& i_time, const double& i_InitialHeight, const double& i_mass,
	const double& i_AirDensity, const double& i_DragCoefficient,
	const double& i_Area, double& o_VerticalPosition)
{
	double terminalVel = 0.0;
	double velocity = 0.0;
	
	PE::BasicNewtonianPhysics::ComputeTerminalVelocity(i_mass, i_AirDensity,
		i_DragCoefficient, i_Area, terminalVel);
		o_VerticalPosition = i_InitialHeight - ((terminalVel * terminalVel) / g) * log(cosh((g * i_time) / terminalVel));
}