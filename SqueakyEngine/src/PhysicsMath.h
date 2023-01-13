#pragma once
class AABB;
struct Sphere;
//#include "Components/Physics/Geometry.h"
class PhysicsBody;
class Collider;


class PhysicsMath
{
public:
    //6.673e-11;
    static constexpr float G = 10.00000000006673f; //6.673e-11 * 1e-24 / (6.673e-11 ) ;
    static constexpr float PHYSICS_SCALE = 1.0f;

    static void SimpleVerletMotion(PhysicsBody& body, float deltaTime);

    static void RigidBodyRotation(PhysicsBody& body, float deltaTime);


    static void GravityOrbit(PhysicsBody& body1, PhysicsBody& body2);
    static bool CheckColliders(PhysicsBody& shape1, PhysicsBody& shape2);
    static void SimpleCollisionResponse(PhysicsBody* body, const AABB* shape);
    static void SimpleCollisionResponse(PhysicsBody* body, const Sphere* shape);

    static void CollisionResponse(PhysicsBody* body1, PhysicsBody* body2);
};
