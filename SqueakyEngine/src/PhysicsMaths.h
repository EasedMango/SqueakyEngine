#pragma once
#include "Components/PhysicsBody.h"
struct Plane;
class PhysicsBody;

class PhysicsMaths
{
public:
	static void SimpleVerletMotion(PhysicsBody& body, float deltaTime);

	static void RigidBodyRotation(PhysicsBody& body, float deltaTime);

	static bool CheckColliders(PhysicsBody& shape1, PhysicsBody& shape2);

	static inline void ApplyTorque(PhysicsBody& object, float torque) { object.SetAngularAcceleration(torque / object.GetRotationalInertia()); };
	static inline void ApplyForce(PhysicsBody& object, glm::vec3 force) { object.SetAccel(force / object.GetMass()); };

	// Collision detection methods:
	static bool SphereSphereCollisionDetected(const PhysicsBody& phyObj1, const PhysicsBody& phyObj2);
	static bool SpherePlaneCollisionDetected(const PhysicsBody& phyObj2, const Plane& plane);
	static bool SphereAABCollisionDetected(const PhysicsBody& phyObj1, const PhysicsBody& phyObj2);

	// Collision response methods:
	static void SphereSphereCollisionResponse(PhysicsBody& phyObj1, PhysicsBody& phyObj2, float& e);
	static void SphereStaticSphereCollisionResponse(PhysicsBody& phyObj1, const PhysicsBody& phyObj2);
	static void SpherePlaneCollisionResponse(PhysicsBody& phyObj1, const Plane& plane);
	static void SphereAABCollisionResponse(PhysicsBody& phyObj1, const PhysicsBody& phyObj2);

	static void CollisionResponse(PhysicsBody& body1, PhysicsBody& body2);
};

