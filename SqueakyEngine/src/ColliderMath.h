#pragma once
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
struct Plane;
class AABB;
struct Ray;
struct Sphere;
class PhysicsBody;
class ColliderMath
{
public:
	static bool RaySphereCollisionDetected(const Ray& ray, const Sphere& sphere);
	static glm::vec3 RaySphereCollisionPoint(const Ray& ray, const Sphere& sphere);
	static glm::vec4 QuadraticEqn(const Ray& ray, const Sphere& sphere);

	static bool RayAABCollisionDetected(const Ray& ray, const AABB& box);
	static glm::vec3 RayAABCollisionPoint(const Ray& ray, const AABB& box);


	static bool SphereSphereCollisionDetected(const PhysicsBody& p1, const PhysicsBody& p2);
	static bool SpherePlaneCollisionDetected(const PhysicsBody& phyObj2, const PhysicsBody& plane);
	static bool SphereAABCollisionDetected(const PhysicsBody& phyObj1, const PhysicsBody& phyObj2);

	static void SphereSphereCollisionResponse(PhysicsBody& phyObj1, PhysicsBody& phyObj2);
	
};

