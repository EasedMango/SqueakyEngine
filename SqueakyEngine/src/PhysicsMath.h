#pragma once
#include "PhysicsBody.h"
class PhysicsMath
{
public:
	//6.673e-11;
	static constexpr float G = 10.00000000006673f;//6.673e-11 * 1e-24 / (6.673e-11 ) ;
	static constexpr float physicsScale = 1.0f;

	static void const SimpleVerletMotion(PhysicsBody& body, const float deltaTime);

	static void const RigidBodyRotation(PhysicsBody& body, const float deltaTime);


	static void const GravityOrbit(PhysicsBody& body1, PhysicsBody& body2);

};

