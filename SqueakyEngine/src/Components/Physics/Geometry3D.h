//#pragma once
//#include <glm/vec3.hpp>
//#include <glm/matrix.hpp>
//#include <glm/geometric.hpp>
//#include "ExtraMath.h"
//
//namespace Geometry
//{
//    //class Geometry3D
//    //{
//
//    //public:
//
//    struct Shape
//    {
//    };
//
//    struct Line
//    {
//        glm::vec3 start;
//        glm::vec3 end;
//
//        Line()
//        {
//        }
//
//        Line(const glm::vec3& s, const glm::vec3& e) :
//            start(s), end(e)
//        {
//        }
//
//        float Length(const Line& line)
//        {
//            return length(line.start - line.end);
//        }
//
//        float LengthSq(const Line& line)
//        {
//            return ExtraMath::MagSqr(line.start - line.end);
//        }
//    };
//
//    struct Ray
//    {
//        glm::vec3 origin;
//        glm::vec3 direction;
//
//        Ray() : origin(0.f), direction(0.f, 0.f, 1.f)
//        {
//        }
//
//        Ray(const glm::vec3& origin_, const glm::vec3& direction_) : origin(origin_), direction(direction_)
//        {
//            direction = normalize(direction);
//        }
//    };
//
//    //using Sphere = Geometry::Sphere;
//    struct Sphere : public Shape
//    {
//        glm::vec3 origin;
//        float radius;
//
//        Sphere() : origin(0.f), radius(0.f)
//        {
//        }
//
//        Sphere(const glm::vec3& origin_, const float& rad) : origin(origin_), radius(rad)
//        {
//        }
//    };
//
//    struct AABB : public Shape
//    {
//        glm::vec3 origin;
//        glm::vec3 size;
//
//        AABB() : origin(0.f), size(0.f, 0.f, 1.f)
//        {
//        }
//
//        AABB(const glm::vec3& origin_, const glm::vec3& size_) : origin(origin_), size(size_)
//        {
//        }
//
//        AABB(const glm::vec3& min, const glm::vec3& max, bool minMax)
//        {
//            origin = (min + max) * 0.5f;
//            size = (max - min) * 0.5f;
//        }
//
//        glm::vec3 GetMin() const
//        {
//            glm::vec3 p1 = origin + size;
//            glm::vec3 p2 = origin - size;
//
//            return glm::vec3(fminf(p1.x, p2.x),
//                             fminf(p1.y, p2.y),
//                             fminf(p1.z, p2.z));
//        }
//
//        glm::vec3 GetMax() const
//        {
//            glm::vec3 p1 = origin + size;
//            glm::vec3 p2 = origin - size;
//
//            return glm::vec3(fmaxf(p1.x, p2.x),
//                             fmaxf(p1.y, p2.y),
//                             fmaxf(p1.z, p2.z));
//        }
//
//        AABB MinkowskiDifference(AABB other)
//        {
//            glm::vec3 topLeft = GetMin() - other.GetMax();
//            glm::vec3 fullSize = size + other.size;
//            return AABB(topLeft, fullSize / 2.0f);
//        }
//
//        glm::vec3 ClostestPointOnBoundsToPoint(const glm::vec3& point)
//        {
//            glm::vec3 min = GetMin();
//            glm::vec3 max = GetMax();
//            float minDist = abs(point.x - min.x);
//            glm::vec3 boundsPoint(min.x, point.y, point.z);
//
//            if (abs(max.x - point.x) < minDist)
//            {
//                minDist = abs(max.x - point.x);
//                boundsPoint = glm::vec3(max.x, point.y, point.z);
//            }
//
//            if (abs(max.y - point.y) < minDist)
//            {
//                minDist = abs(max.y - point.y);
//                boundsPoint = glm::vec3(point.x, max.y, point.z);
//            }
//
//            if (abs(min.y - point.y) < minDist)
//            {
//                minDist = abs(min.y - point.y);
//                boundsPoint = glm::vec3(point.x, min.y, point.z);
//            }
//
//            if (abs(max.z - point.z) < minDist)
//            {
//                minDist = abs(min.y - point.y);
//                boundsPoint = glm::vec3(point.x, point.y, max.z);
//            }
//            if (abs(min.z - point.z) < minDist)
//            {
//                minDist = abs(min.y - point.y);
//                boundsPoint = glm::vec3(point.x, point.y, min.z);
//            }
//            return boundsPoint;
//        }
//    };
//
//    struct OBB
//    {
//        glm::vec3 origin;
//        glm::vec3 size;
//        glm::mat3 orientation;
//
//        OBB() : size(1, 1, 1)
//        {
//        }
//
//        OBB(const glm::vec3& p, const glm::vec3& s) :
//            origin(p), size(s)
//        {
//        }
//
//        OBB(const glm::vec3& p, const glm::vec3& s, const glm::mat3& o)
//            : origin(p), size(s), orientation(o)
//        {
//        }
//    };
//
//    struct Plane
//    {
//        glm::vec3 normal;
//        float distance;
//
//        Plane() : normal(1, 0, 0)
//        {
//        }
//
//        Plane(const glm::vec3& n, float d) :
//            normal(n), distance(d)
//        {
//        }
//
//        float PlaneEquation(const glm::vec3& point)
//        {
//            return dot(point, normal) - distance;
//        }
//    };
//
//    struct Triangle
//    {
//        glm::vec3 a;
//        glm::vec3 b;
//        glm::vec3 c;
//
//        Triangle()
//        {
//        }
//
//        Triangle(const glm::vec3& p1, const glm::vec3& p2,
//                 const glm::vec3& p3) : a(p1), b(p2), c(p3)
//        {
//        }
//    };
//};
