#include "PhysicsMath.h"
#include <glm/geometric.hpp>
#include <iostream>
#include "Components/PhysicsBody.h"

void const PhysicsMath::SimpleVerletMotion(PhysicsBody& body, const float deltaTime)
{
	//std::cout << "G: " << G << std::endl;
	body.SetPos(body.GetPos() + body.GetVel() * deltaTime + (0.5f * body.GetPrevAccel() * deltaTime * deltaTime));

	body.SetVel(body.GetVel() + 0.5f * (body.GetPrevAccel() + body.GetAccel()) * deltaTime);

	body.SetPrevAccel(body.GetAccel());
}

void const PhysicsMath::RigidBodyRotation(PhysicsBody& body, const float deltaTime)
{
	float rotInrt = body.GetMass() * (body.GetScale().x * body.GetScale().x);
	body.SetAngle(body.GetAngle() + body.GetAngularVelocity() * deltaTime + 0.5f * body.GetAngularAcceleration() * deltaTime * deltaTime);
	body.SetAngularVelocity(body.GetAngularVelocity() + body.GetAngularAcceleration() * deltaTime);

	body.SetRotation((body.GetRotation() + body.GetRotVel() * deltaTime) + (0.5f * body.GetRotAccel() * deltaTime * deltaTime));
	body.SetRotVel(body.GetRotVel() + body.GetRotAccel() * deltaTime);
}

void const PhysicsMath::GravityOrbit(PhysicsBody& body1, PhysicsBody& body2)
{

	glm::vec3 direction = body2.GetPos() - body1.GetPos();
	float distance = glm::length(direction);
	float mass = (G* body1.GetMass() * body2.GetMass()) / powf(distance, 2.0f);
	glm::vec3 normal = direction / distance;
	glm::vec3 f = mass * normal;
	body1.AddForce(f);

	direction = body1.GetPos() - body2.GetPos();
	distance = glm::length(direction);
	mass = G * (body2.GetMass() * body1.GetMass()) / powf(distance, 2.0f);
	normal = direction / distance;
	f = mass * normal;
	body2.AddForce(f);
}
