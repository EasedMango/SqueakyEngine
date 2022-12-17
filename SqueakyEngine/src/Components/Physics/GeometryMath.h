//#pragma once
//#include "Geometry3D.h"
//
//namespace Geometry
//{
//    class GeometryMath
//    {
//    public:
//        static bool PointInSphere(const glm::vec3& point, const Sphere& sphere);
//        static glm::vec3 ClosestPoint(const Sphere& sphere, const glm::vec3& point);
//        static bool PointInAABB(const glm::vec3& point, const AABB& aabb);
//        static glm::vec3 ClosestPoint(const AABB& aabb, const glm::vec3& point);
//        static bool PointInOBB(const glm::vec3& point, const OBB& obb);
//        static glm::vec3 ClosestPoint(const OBB& obb, const glm::vec3& point);
//        static bool PointOnPlane(const glm::vec3& point, const Plane& plane);
//        static glm::vec3 ClosestPoint(const Plane& plane, const glm::vec3& point);
//        static bool PointOnLine(const glm::vec3& point, const Line& line);
//        static glm::vec3 ClosestPoint(const Line& line, const glm::vec3& point);
//        static bool PointOnRay(const glm::vec3& point, const Ray& ray);
//        static glm::vec3 ClosestPoint(const Ray& ray, const glm::vec3& point);
//
//        static glm::vec3 GetCollisionDepth(const AABB& aabb1, const AABB& aabb2);
//
//        static bool Raycast(Ray d,const  AABB a, float& tmin, glm::vec3& point);
//        static bool SphereSphere(Sphere s1, Sphere s2);
//        static bool AABBAABB(const AABB& aabb1, const AABB& aabb2);
//        static bool SphereAABB(const Sphere& sphere, const AABB& aabb);
//        static bool Collision(const Sphere& s1, const Sphere& s2);
//        static bool Collision(const AABB& aabb1, const AABB& aabb2);
//        static bool Collision(const Sphere& sphere, const AABB& aabb);
//        static bool Collision(const AABB& aabb, const Sphere& sphere);
//    };
//}
