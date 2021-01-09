#include "Projectile.h" 
void PE::Projectile::TrajectoryGravityOnlyModel(std::shared_ptr<GameObject> io_GameObject, const glm::vec3& i_InitialVelocity, const glm::vec3& i_InitialPosition, const float& i_Time)
{
	glm::vec3 velocity;
	glm::vec3 position;
	io_GameObject->GetVelocity(velocity);
	io_GameObject->GetPosition(position);
	// X velocity. 
	velocity.x = i_InitialVelocity.x;
	// Z velocity. 
	velocity.z = i_InitialVelocity.z;
	// Y velocity. 
	velocity.y = i_InitialVelocity.y - (9.81f*i_Time);

	io_GameObject->SetVelocity(velocity);
	// X displacement. 
	position.x = i_InitialPosition.x + (velocity.x *i_Time);
	// Z displacment. 
	position.z = i_InitialPosition.z + (velocity.z *i_Time);
	// Y displacement.
	position.y = i_InitialPosition.y + (velocity.y *i_Time) -
	(0.5f*9.81f*i_Time*i_Time);

	io_GameObject->SetPosition(position);
}
void PE::Projectile::TrajectoryDragForceOnly(GameObject& io_GameObject, const float& i_Time)
{

	// Look at the implementation of this function in our case study 
}
void PE::Projectile::TrajectoryDragAndWind(GameObject& io_GameObject, const glm::vec3& i_WindVelocity, const float& i_Time) {

	// Look at the implementation of this function in our case study. 
}
void PE::Projectile::TrajectoryDragWindAndSpin(GameObject& io_GameObject, const glm::vec3& i_WindVelocity, const float& i_Time) {
	// Look at the implementation of this function in our case study. 
}
