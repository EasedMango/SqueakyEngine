#include "PhysicsMath.h"
#include <glm/geometric.hpp>
#include <iostream>
#include <variant>
#include "Components/PhysicsBody.h"
#include "Components/Collider.h"

#include "Components/Actor.h"
#include "Vec.h"
#include "Components/Physics/OBB.h"
#include "Components/Physics/Sphere.h"
#include "ColliderMath.h"
#include "Components/Physics/OBB.h"
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




bool PhysicsMath::CheckColliders(PhysicsBody& shape1, PhysicsBody& shape2)
{

	if (const auto  tempA = shape1.GetShape<OBB>(); tempA != nullptr)
	{
		OBB ab = *tempA;
		ab.center = shape1.GetPos();
		ab.rotation = mat3_cast(shape1.GetRotation());
		mat4 rot1 = mat4_cast(-shape1.GetRotation());
		if (const auto  tempB = shape2.GetShape<OBB>(); tempB != nullptr)
		{
			OBB bc = *tempB;
			bc.center = shape2.GetPos();
			bc.rotation = mat3_cast( shape2.GetRotation());
	

			ColliderMath::CollisionResult detect = ColliderMath::OBBOBBCollision(ab, bc);

			if (detect.collide) {
				shape1.GetCollider()->AddHandle(shape2.GetCollider());
				shape2.GetCollider()->AddHandle(shape1.GetCollider());
				CollisionResponse(&shape1, &shape2, detect.penetrationDepth);
			}
			return detect.collide;
		}
		if (const auto  bc = shape2.GetShape<Sphere>(); bc != nullptr)
		{
			bc->pos = shape2.GetPos();
			float ma = 0;

			ColliderMath::CollisionResult detect = ColliderMath::OBBSphereCollision(ab, *bc);
			if (detect.collide) {
				shape1.GetCollider()->AddHandle(shape2.GetCollider());
				shape2.GetCollider()->AddHandle(shape1.GetCollider());
				CollisionResponse(&shape1, &shape2, detect.penetrationDepth);
			}
			return detect.collide;
		}
	}
	if (const auto  ab = shape1.GetShape<Sphere>(); ab != nullptr)
	{

		ab->pos = shape1.GetPos();

		if (const auto  bc = shape2.GetShape<OBB>(); bc != nullptr)
		{


			OBB tempBC = *bc;
			tempBC.center = shape2.GetPos();
			tempBC.rotation = mat3_cast(shape2.GetRotation());
			
			ColliderMath::CollisionResult detect = ColliderMath::OBBSphereCollision(tempBC, *ab);
			if (detect.collide) {
				shape1.GetCollider()->AddHandle(shape2.GetCollider());
				shape2.GetCollider()->AddHandle(shape1.GetCollider());
				CollisionResponse(&shape1, &shape2,detect.penetrationDepth);
			}

			return detect.collide;
		}
		if (const auto  bc = shape2.GetShape<Sphere>(); bc != nullptr)
		{
			bc->pos = shape2.GetPos();
			float ma = 0;
			ColliderMath::CollisionResult detect = ColliderMath::SphereSphereCollision(*ab, *bc);//false;//TestMovingSphereSphere(*ab, *bc, shape1->GetVel(), shape2->GetVel(), ma);
			if (detect.collide) {
				shape1.GetCollider()->AddHandle(shape2.GetCollider());
				shape2.GetCollider()->AddHandle(shape1.GetCollider());
				CollisionResponse(&shape1, &shape2, detect.penetrationDepth);
			}
			return detect.collide;
		}
	}
	return false;
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
void PhysicsMath::CollisionResponse(PhysicsBody* body1, PhysicsBody* body2, const float& depthPen)
{
	if (body1->GetIsStatic() && body2->GetIsStatic())
		return;

	const vec3 n = normalize(body1->GetPos() - body2->GetPos());

	Logger::Info(std::string("Depth: ").append(std::to_string(depthPen)));
	if (all(isnan(n)))
	{
		return;
	}
	const float e = 0.9f;


	const float p1 = (dot(-body1->GetVel(), n));
	//std::cout << "p1: " << p1 << std::endl;

	const float p2 = (dot(-body2->GetVel(), n));
	//std::cout << "p2: " << p2 << std::endl;

	vec3 forceOne;
	vec3 forceTwo;
	if (!body1->GetIsStatic())
	{
		const float vf2 = ((((body1->GetMass() * p1) + (body2->GetMass() * p2))
			+ ((body1->GetMass() * e * p1) - (body1->GetMass() * e * p2)))) / (body1->GetMass() + body2->GetMass());
		//std::cout << "vf2: " << vf2 << std::endl;
		forceOne = ((vf2 - p2) * n) + (n * depthPen) * 1.001f;

		//body1->SetVel(((vf2 - p2) * n) + (n * depthPen) * 1.001f);
		//printf("b1: ");
		//printVec(((vf2 - p2) * n) * 1.15f);
	}
	if (!body2->GetIsStatic())
	{
		const float vf1 = ((((body1->GetMass() * p1) + (body2->GetMass() * p2))
			+ ((body2->GetMass() * e * p2) - (body2->GetMass() * e * p1)))) / (body1->GetMass() + body2->GetMass());
		//std::cout << "vf1: " << vf1 << std::endl;

		forceTwo = ((vf1 - p1) * n) - (n * depthPen) * 1.001f;

		//	body2->SetVel(((vf1 - p1) * n) - (n * depthPen) * 1.001f);
			//printf("b2: ");
			//printVec(((vf1 - p1) * n) * 1.15f);
	}
	if (!body1->GetIsStatic())
	{
		body1->SetPos(body1->GetPos() + (n * depthPen) * 1.001f);
		//vec3 mag = (body1->GetMass() * (forceOne - body2->GetVel()));

		body1->SetVel(forceOne);
	}
	if (!body2->GetIsStatic())
	{
		body2->SetPos(body2->GetPos() - (n * depthPen) * 1.001f);
		//vec3 mag = (body2->GetMass() * (forceTwo - body1->GetVel()));

		//float springed = -50 * depthPen - 0.1f * length(forceTwo);
		body2->SetVel(forceTwo);
	}
}
void PhysicsMath::CollisionResponse(PhysicsBody* body1, PhysicsBody* body2, const float& penetration, const float& e)
{
	// calculate relative velocity
	vec3 relativeVelocity = body2->GetVel() - body1->GetVel();
	vec3 normal = normalize(body1->GetPos() - body2->GetPos());
	// calculate relative velocity in terms of the normal direction
	float velAlongNormal = dot(relativeVelocity, normal);

	// only move the objects if they are approaching each other
	if (velAlongNormal > 0)
		return;

	// calculate impulse scalar
	float j = -(1 + e) * velAlongNormal;
	j /= -body1->GetMass() +- body2->GetMass();

	// apply impulse
	vec3 impulse = j * normal;
	if (!body1->GetIsStatic())
		body1->SetVel(body1->GetVel() - -body1->GetMass() * impulse);
	if (!body2->GetIsStatic())
		body2->SetVel(body2->GetVel() + -body2->GetMass() * impulse);

	// positional correction to prevent sinking
	const float percent = 0.4f;
	const float slop = 0.01f;
	vec3 correction = max(penetration - slop, 0.0f) / (-body1->GetMass() +- body2->GetMass()) * percent * normal;
	if (!body1->GetIsStatic())
		body1->SetPos(body1->GetPos() - -body1->GetMass() * correction);
	if (!body2->GetIsStatic())
		body2->SetPos(body2->GetPos() +


			-body2->GetMass() * correction);
}