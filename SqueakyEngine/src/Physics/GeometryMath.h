#pragma once
#include "Geometry3D.h"

namespace Geometry {

    class GeometryMath
    {
        
        static bool PointInSphere(const glm::vec3& point,const Sphere& sphere);
        static glm::vec3 ClosestPoint(const Sphere& sphere, const glm::vec3& point);
        static bool PointInAABB(const glm::vec3& point, const AABB& aabb);
        static glm::vec3 ClosestPoint(const AABB& aabb, const glm::vec3& point);
        static bool PointInOBB(const glm::vec3& point, const OBB& obb);
        static glm::vec3 ClosestPoint(const OBB& obb, const glm::vec3& point);
        static bool PointOnPlane(const glm::vec3& point, const Plane& plane);
        static glm::vec3 ClosestPoint(const Plane& plane, const glm::vec3& point);
        static bool PointOnLine(const glm::vec3& point, const Line& line);
        static glm::vec3 ClosestPoint(const Line& line, const glm::vec3& point);
        static bool PointOnRay(const glm::vec3& point, const Ray& ray);
        static glm::vec3 ClosestPoint(const Ray& ray, const glm::vec3& point);
    };

}