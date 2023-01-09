#include "PhysicsMath.h"
#include <glm/geometric.hpp>
#include <iostream>
#include <variant>
#include "Components/PhysicsBody.h"
#include "Components/Collider.h"

#include "Components/Actor.h"
#include "Vec.h"
#include "Components/Physics/Geometry.h"

using namespace glm;

void PhysicsMath::SimpleVerletMotion(PhysicsBody& body, const float deltaTime)
{
	//std::cout << "G: " << G << std::endl;
	body.SetPos(body.GetPos() + body.GetVel() * deltaTime + (0.5f * body.GetPrevAccel() * deltaTime * deltaTime));

	body.SetVel(body.GetVel() + 0.5f * (body.GetPrevAccel() + body.GetAccel()) * deltaTime);

	body.SetPrevAccel(body.GetAccel());
}


void PhysicsMath::RigidBodyRotation(PhysicsBody& body, const float deltaTime)
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

void PhysicsMath::GravityOrbit(PhysicsBody& body1, PhysicsBody& body2)
{
	vec3 direction = body2.GetPos() - body1.GetPos();
	float distance = length(direction);
	float mass = (G * body1.GetMass() * body2.GetMass()) / powf(distance, 2.0f);
	vec3 normal = direction / distance;
	vec3 f = mass * normal;
	body1.AddForce(f);

	direction = body1.GetPos() - body2.GetPos();
	distance = length(direction);
	mass = G * (body2.GetMass() * body1.GetMass()) / powf(distance, 2.0f);
	normal = direction / distance;
	f = mass * normal;
	body2.AddForce(f);
}

bool PhysicsMath::CheckColliders(PhysicsBody* shape1, PhysicsBody* shape2)
{

	if (const auto  ab= shape1->GetShape<Geometry::AABB>();ab!=nullptr)
	{
		
		ab->center = shape1->GetPos();

		if (const auto  bc = shape2->GetShape<Geometry::AABB>(); bc != nullptr)
		{

			bc->center = shape2->GetPos();
			float ma = 0;
			float mt = 0;
			return Geometry::IntersectMovingAABBAABB(*ab, *bc,shape1->GetVel(),shape2->GetVel(),ma,mt);
		}
		if (const auto  bc = shape2->GetShape<Geometry::Sphere>(); bc != nullptr)
		{
			bc->center = shape2->GetPos();
			float ma = 0;
			return false;
		}
	}
	if (const auto  ab = shape1->GetShape<Geometry::Sphere>(); ab != nullptr)
	{

		ab->center = shape1->GetPos();

		if (const auto  bc = shape2->GetShape<Geometry::AABB>(); bc != nullptr)
		{

			bc->center = shape2->GetPos();
			float ma = 0;
			float mt = 0;
			return false;
		}
		if (const auto  bc = shape2->GetShape<Geometry::Sphere>(); bc != nullptr)
		{
			bc->center = shape2->GetPos();
			float ma = 0;
			return Geometry::TestMovingSphereSphere(*ab, *bc, shape1->GetVel(), shape2->GetVel(), ma);
		}
	}
	return false;
}



void PhysicsMath::SimpleCollisionResponse(PhysicsBody* body, const Geometry::AABB* shape)
{
	// std::cout << dynamic_cast<Actor*>(body->GetParent())->GetName() << " is colliding\n";
	const vec3 n = normalize(body->GetPos() - shape->center);
	if (all(isnan(n)))
	{
		return;
	}

	const vec3 p = dot(-body->GetVel(), n) * n;
	const vec3 v = body->GetVel() + (2.0f * p);


	body->SetVel(v);
}

void PhysicsMath::SimpleCollisionResponse(PhysicsBody* body, const Geometry::Sphere* shape)
{
	const vec3 n = normalize(body->GetPos() - shape->center);
	const vec3 p = dot(-body->GetVel(), n) * n;
	const vec3 v = body->GetVel() + (2.0f * p);


	body->SetVel(v);
}

void PhysicsMath::CollisionResponse(PhysicsBody* body1, PhysicsBody* body2)
{
	if (body1->GetIsStatic() && body2->GetIsStatic())
		return;

	const vec3 n = normalize(body1->GetPos() - body2->GetPos());

	if (all(isnan(n)))
	{
		return;
	}
	const float e = 0.25f;


	const float p1 = (dot(-body1->GetVel(), n));
	//std::cout << "p1: " << p1 << std::endl;

	const float p2 = (dot(-body2->GetVel(), n));
	//std::cout << "p2: " << p2 << std::endl;


	if (!body1->GetIsStatic())
	{
		const float vf2 = ((((body1->GetMass() * p1) + (body2->GetMass() * p2))
			+ ((body1->GetMass() * e * p1) - (body1->GetMass() * e * p2)))) / (body1->GetMass() + body2->GetMass());
		//std::cout << "vf2: " << vf2 << std::endl;
		body1->SetPos(body1->GetPos() + (n * 0.001f));
		body1->SetVel(((vf2 - p2) * n) * 1.f);
		//printf("b1: ");
		//printVec(((vf2 - p2) * n) * 1.15f);
	}
	if (!body2->GetIsStatic())
	{
		const float vf1 = ((((body1->GetMass() * p1) + (body2->GetMass() * p2))
			+ ((body2->GetMass() * e * p2) - (body2->GetMass() * e * p1)))) / (body1->GetMass() + body2->GetMass());
		//std::cout << "vf1: " << vf1 << std::endl;
		body2->SetPos(body2->GetPos() - (n * 0.001f));
		body2->SetVel(((vf1 - p1) * n) * 1.f);
		//printf("b2: ");
		//printVec(((vf1 - p1) * n) * 1.15f);
	}
}
