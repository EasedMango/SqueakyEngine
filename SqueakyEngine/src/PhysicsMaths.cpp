#include "PhysicsMaths.h"
#include "Components/PhysicsBody.h"
#include "PhysicsMaths.h"
#include <glm/geometric.hpp>
#include <iostream>
#include <variant>
#include "Components/PhysicsBody.h"
#include "Components/Collider.h"

#include "Components/Actor.h"
#include "Vec.h"
#include "Components/Physics/Geometry.h"
void PhysicsMaths::SimpleVerletMotion(PhysicsBody& body, const float deltaTime)
{
	//std::cout << "G: " << G << std::endl;
	body.SetPos(body.GetPos() + body.GetVel() * deltaTime + (0.5f * body.GetPrevAccel() * deltaTime * deltaTime));

	body.SetVel(body.GetVel() + 0.5f * (body.GetPrevAccel() + body.GetAccel()) * deltaTime);

	body.SetPrevAccel(body.GetAccel());
}

void PhysicsMaths::RigidBodyRotation(PhysicsBody& body, const float deltaTime)
{
	//float rotInrt = body.GetMass() * (body.GetScale().x * body.GetScale().x);
	body.SetAngle(
		body.GetAngle() + body.GetAngularVelocity() * deltaTime + 0.5f * body.GetAngularAcceleration() * deltaTime *
		deltaTime);
	body.SetAngularVelocity(body.GetAngularVelocity() + body.GetAngularAcceleration() * deltaTime);

	//body.SetRotation(
	//	(body.GetRotation() + body.GetRotVel() * deltaTime) + (0.5f * body.GetRotAccel() * deltaTime * deltaTime));
	//body.SetRotVel(body.GetRotVel() + body.GetRotAccel() * deltaTime);
}

bool PhysicsMaths::CheckColliders(PhysicsBody& shape1, PhysicsBody& shape2)
{
	return false;
}






void PhysicsMaths::CollisionResponse(PhysicsBody& body1, PhysicsBody& body2)
{
}
