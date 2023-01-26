#pragma once
#include <glm/matrix.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
struct OBB;
struct Plane;
struct AABB;
struct Ray;
struct Sphere;
class PhysicsBody;
class ColliderMath
{
public:
	struct CollisionResult {
		bool collide;
		glm::vec3 closestPoint;
		float penetrationDepth;
	};

	static bool RaySphereCollisionDetected(const Ray& ray, const Sphere& sphere);
	static glm::vec3 RaySphereCollisionPoint(const Ray& ray, const Sphere& sphere);
	static glm::vec4 QuadraticEqn(const Ray& ray, const Sphere& sphere);



	static CollisionResult OBBSphereCollision(const OBB& box, const Sphere& sphere);
	static CollisionResult OBBOBBCollision(const OBB& box1,const OBB& box2);
	static CollisionResult SphereSphereCollision(const Sphere& p1, const Sphere& p2);






	
	//static bool SpherePlaneCollisionDetected(const PhysicsBody& phyObj2, const PhysicsBody& plane);
	//static bool SphereAABCollisionDetected(const PhysicsBody& phyObj1, const PhysicsBody& phyObj2);


	
};

