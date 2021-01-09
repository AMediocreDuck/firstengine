#include "CollisionDetection.h" 
void PE::CollisionDetection::SphereToPointOnPlane(GameObject& i_GameObject, glm::vec3& i_PointOnPlane, glm::vec3& i_Normal, float& o_Distance, bool& o_collision)
{
	glm::vec3 centerA(0.0f, 0.0f, 0.0f);  	
	glm::vec3 radiusA(0.0f, 0.0f, 0.0f);  	
	i_GameObject.GetPosition(centerA);  	
	i_GameObject.GetScale(radiusA);  	
	glm::vec3 v = centerA.y - i_PointOnPlane;  	
	float distance = glm::dot(v, i_Normal);
	if (distance > radiusA.y / 2.0f)
	{
		o_collision = false;
	}
	else
	{
		o_collision = true;  	o_Distance = distance;
	}
}
void PE::CollisionDetection::SphereToSphere(GameObject& i_GameObjectA, GameObject& i_GameObjectB, glm::vec3& o_ContactPoint, bool& o_Collision)
{
	glm::vec3 centerA(0.0f, 0.0f, 0.0f);  	
	glm::vec3 centerB(0.0f, 0.0f, 0.0f);  	
	glm::vec3 radiusA(0.0f, 0.0f, 0.0f);  	
	glm::vec3 radiusB(0.0f, 0.0f, 0.0f);  	
	float distance = 0.0f;  	
	i_GameObjectA.GetPosition(centerA);  	
	i_GameObjectB.GetPosition(centerB);  	
	i_GameObjectA.GetScale(radiusA);  	
	i_GameObjectB.GetScale(radiusB);  	
	distance = glm::distance(centerA, centerB);  	
	glm::vec3 normalised(centerA - centerB);
	float mag = normalised.x*normalised.x + normalised.y*normalised.y + normalised.z*normalised.z;
	mag = static_cast<float>(sqrt(static_cast<double>(mag)));
	normalised = normalised / mag;  	
	if (distance < (radiusA.y / 2.0f + radiusB.y / 2.0f))
	{
		o_ContactPoint = normalised * radiusA.y;
		o_Collision = true;
	}
	else
	{
		o_Collision = false;
	}

}
void PE::CollisionDetection::SphereToSphereWithTime(GameObject& i_GameObjectA, GameObject& i_GameObjectB, glm::vec3& o_ContactPoint, double& o_Time, bool& o_Collision)
{
	glm::vec3 velA(0.0f, 0.0f, 0.0f);  	
	glm::vec3 velB(0.0f, 0.0f, 0.0f);  	
	glm::vec3 cenA(0.0f, 0.0f, 0.0f);  	
	glm::vec3 cenB(0.0f, 0.0f, 0.0f);  	
	glm::vec3 radA(0.0f, 0.0f, 0.0f);  	
	glm::vec3 radB(0.0f, 0.0f, 0.0f);

	i_GameObjectA.GetVelocity(velA);  	
	i_GameObjectA.GetPosition(cenA);  	
	i_GameObjectA.GetScale(radA);

	i_GameObjectB.GetVelocity(velB);  	
	i_GameObjectB.GetPosition(cenB);  	
	i_GameObjectB.GetScale(radB);

	glm::vec3 s = (cenA - cenB);  	
	glm::vec3 v = (velA - velB);  	
	glm::vec3 normalised(cenA - cenB);

	float sumOfRadii = radA.y / 2.0f + radB.y / 2.0f;
	float a = glm::dot(v, v);  	float b = glm::dot(v, s);
	float c = glm::dot(s, s) - (sumOfRadii * sumOfRadii);
	float dist = glm::dot(s, s);  	
	float d = (b * b) - (a * dist); 
	float mag = normalised.x*normalised.x + normalised.y*normalised.y + normalised.z*normalised.z;
	mag = static_cast<float>(sqrt(static_cast<double>(mag)));
	normalised = normalised / mag;  	std::cout << std::setprecision(4);  	
	if (c < 0.0f) // if zero or gone negative, they overlap 
	{
		o_ContactPoint = normalised * radA.y;
		o_Collision = true;
		o_Time = 0.0;
	}
	else if (b >= 0.0f)// does not move towards each other 
	{
		o_Time += 1.0;
	}
	else if (d >= 0.0f)//  Calculate time to collision. 
	{
		o_Time = static_cast<float>((-b - sqrt(d)) / a);
	}
}


void PE::CollisionDetection::AABB(GameObject& i_GameObjectA,
	GameObject& i_GameObjectB, bool& o_CollisionDetection)
{

	bool x_Collision, y_Collision, z_Collision;
	glm::vec3 centerA(0.0f, 0.0f, 0.0f), centerB(0.0f, 0.0f, 0.0f), sizeA(0.0f, 0.0f, 0.0f), sizeB(0.0f, 0.0f, 0.0f); x_Collision = false;
	y_Collision = false;

	z_Collision = false;
	i_GameObjectA.GetPosition(centerA);
	i_GameObjectB.GetPosition(centerB);
	i_GameObjectA.GetScale(sizeA);
	i_GameObjectB.GetScale(sizeB);
	AABBCollisionXYZ((centerA.x - sizeA.x / 2.0f), (centerA.x + sizeA.x / 2.0f), (centerB.x - sizeB.x / 2.0f), (centerB.x + sizeB.x / 2.0f), x_Collision);
	AABBCollisionXYZ((centerA.y - sizeA.y / 2.0f), (centerA.y + sizeA.y / 2.0f), (centerB.y - sizeB.y / 2.0f), (centerB.y + sizeB.y / 2.0f), y_Collision);
	AABBCollisionXYZ((centerA.z - sizeA.z / 2.0f), (centerA.z + sizeA.z / 2.0f), (centerB.z - sizeB.z / 2.0f), (centerB.z + sizeB.z / 2.0f), z_Collision);
	if (x_Collision && y_Collision && z_Collision)
		o_CollisionDetection = true;
	else

		o_CollisionDetection = false;
}
void PE::CollisionDetection::AABBCollisionXYZ(float i_MinA, float i_MaxA, float i_MinB, float i_MaxB, bool& o_Collision) {
	if (((i_MinA <= i_MinB) && (i_MaxA >= i_MinB)) || ((i_MaxB >= i_MinA) && (i_MinB <= i_MinA)))
		o_Collision = true;
	else
		o_Collision = false;
}

