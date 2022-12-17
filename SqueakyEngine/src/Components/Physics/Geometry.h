#pragma once
#include <glm/matrix.hpp>
#include <glm/geometric.hpp>


class Geometry
{
public:
	/**
	 * \brief axis-aligned bounding box
	 */
	struct AABB {

		glm::vec3 center;
		glm::vec3 radius;
		AABB(glm::vec3 c, glm::vec3 r) : center(c), radius(r)
		{
			
		}
		glm::vec3 GetMin() const { return center - radius; }
		glm::vec3 GetMax() const { return center + radius; }
		glm::vec3 GetSize() const { return  radius * 2.f; }
	};
	struct Sphere
	{
		glm::vec3 center;
		float radius;
		Sphere(glm::vec3 c, float r) : center(c),radius(r)
		{
			
		}
	};
	struct OBB {
		glm::vec3 c; // OBB center point
		glm::vec3 u[3]; // Local x-, y-, and z-axes
		glm::vec3 e; // Positive halfwidth extents of OBB along each axis
	};

	struct Ray
	{
		glm::vec3 start;
		glm::vec3 dir;

		Ray(const glm::vec3& start_, const glm::vec3& dir_);

		~Ray();

		glm::vec3  CurrentPosition(const float& t) const;;

	};
	struct RayResults
	{
		float distance;
		glm::vec3 point;
	};
	static bool TestAABBAABB(AABB a, AABB b);


	static bool IntersectMovingAABBAABB(AABB a, AABB b, glm::vec3 va, glm::vec3 vb,
		float& tfirst, float& tlast);


	static int TestSphereSphere(Sphere a, Sphere b);
	static int TestMovingSphereSphere(Sphere s0, Sphere s1, glm::vec3 v0, glm::vec3 v1, float& t);

	// Support function that returns the AABB vertex with index n
	static glm::vec3 Corner(AABB b, int n);

	static bool RaySphereCollisionDetected(const Ray& ray, const Sphere& sphere);

	static RayResults RaySphereCollisionPoint(const Ray& ray, const Sphere& sphere);

	static glm::vec4 QuadraticEqn(const Ray& ray, const Sphere& sphere);


	//bool RayAABCollisionDetected(const Ray& ray, const AABB& box)
	//{

	//	return (0 <= ray.dir.x <= -box.planes[3].plane.w && 0 <= ray.dir.y <= -box.planes[4].plane.w && 0 <= ray.dir.z <= -box.planes[5].plane.w)
	//		? true : false;

	//}

	static int TestOBBOBB(OBB& a, OBB& b);

	static void SwapValue(float& a, float& b);
	static int IntersectRaySphere(glm::vec3 p, glm::vec3 d, Geometry::Sphere s, float& t, glm::vec3& q);
	static int TestRaySphere(glm::vec3 p, glm::vec3 d, Geometry::Sphere s);
	static int IntersectRayAABB(glm::vec3 p, glm::vec3 d, AABB a, float& tmin, glm::vec3& q);
};

