#pragma once
#include "Components/PhysicsBody.h"
class CollisionMath
{


	//static inline void ApplyTorque(PhysicsBody& object, float torque) { object.SetAngularAccel(torque / object.GetRotationalInertia()); };
	//static inline void ApplyForce(PhysicsBody& object, Vec3 force) { object.SetAccel(force / object.GetMass()); };

	// Collision detection methods:
	static bool SphereSphereCollisionDetected(PhysicsBody& phyObj1, PhysicsBody& phyObj2);
	//static bool SpherePlaneCollisionDetected(const PhysicsBody& phyObj2, const Plane& plane);
	//static float SphereAABCollisionDetected(const PhysicsBody& phyObj1, const PhysicsBody& phyObj2);

	// Collision response methods:
	static void SphereSphereCollisionResponse(PhysicsBody& phyObj1, PhysicsBody& phyObj2, float& e);
	static void SphereStaticSphereCollisionResponse(PhysicsBody& phyObj1, PhysicsBody& phyObj2);
	//static void SpherePlaneCollisionResponse(PhysicsBody& phyObj1, const Plane& plane);
	//static void SphereAABCollisionResponse(PhysicsBody& phyObj1, const PhysicsBody& phyObj2);


	//static void ApplyForces(PhysicsBody& body, float& waterHeight);
};

