//#include "GeometryMath.h"
//#include "ExtraMath.h"
//#include <iostream>
//
//using namespace glm;
//
//namespace Geometry
//{
//    bool GeometryMath::PointInSphere(const vec3& point, const Sphere& sphere)
//    {
//        //Find the square magnitude of the line between the sphere center and test point as well as the square radius of the sphere:
//        float magSq = ExtraMath::MagSqr(point - sphere.origin);
//        //Compare the square magnitude to the square radius. If the square magnitude is less, the point is inside the sphere:
//        float radSq = sphere.radius * sphere.radius;
//        return magSq < radSq;
//    }
//
//    vec3 GeometryMath::ClosestPoint(const Sphere& sphere, const vec3& point)
//    {
//        //Find a normalized vector from the center of the sphere to the test point :
//        vec3 sphereToPoint = point - sphere.origin;
//        normalize(sphereToPoint);
//        //Resize the normalized vector to the size of the radius :
//        sphereToPoint = sphereToPoint * sphere.radius;
//        //Return the resized vector offset by the position of the sphere :
//        return sphereToPoint + sphere.origin;
//    }
//
//    bool GeometryMath::PointInAABB(const vec3& point, const AABB& aabb)
//    {
//        vec3 min = aabb.GetMin();
//        vec3 max = aabb.GetMax();
//        //The shapes do not intersect if any component of the test point is smaller/larger than the respective component of the min/max point of the AABB :
//        if (point.x < min.x || point.y < min.y || point.z < min.z)
//        {
//            return false;
//        }
//        if (point.x > max.x || point.y > max.y || point.z > max.z)
//        {
//            return false;
//        }
//
//        return true;
//    }
//
//
//    vec3 GeometryMath::ClosestPoint(const AABB& aabb, const vec3& point)
//    {
//        vec3 result = point;
//        vec3 min = aabb.GetMin();
//        vec3 max = aabb.GetMax();
//
//
//        result.x = (result.x < min.x) ? min.x : result.x;
//
//        result.y = (result.y < min.x) ? min.y : result.y;
//        result.z = (result.z < min.x) ? min.z : result.z;
//        result.x = (result.x > max.x) ? max.x : result.x;
//        result.y = (result.y > max.x) ? max.y : result.y;
//        result.z = (result.z > max.x) ? max.z : result.z;
//
//        return result;
//    }
//
//    bool GeometryMath::PointInOBB(const vec3& point, const OBB& obb)
//    {
//        //We are going to move the point relative to the oriented bounding box by subtracting the box position from the point:
//        vec3 dir = point - obb.origin;
//        //This loop will run three times. Iteration 0 is the X axis, iteration 1 is the Y axis, and iteration 2 is the Z axis. 
//        //We will project the point onto each of the local axes of the box and compare the distance to the extent of the box on that axis:
//        for (int i = 0; i < 3; ++i)
//        {
//            vec3 axis =
//                obb.orientation[i * 3];
//            // Next we project the relative point onto that axisand record how far from the origin of the box the projection is :
//            float distance = dot(dir, axis);
//            //If the distance is greater than the extent of the box, or less than the negative extent of the box, the point is not inside the box
//            if (distance > obb.size[i])
//            {
//                return false;
//            }
//            if (distance < -obb.size[i])
//            {
//                return false;
//            }
//        }
//
//        return true;
//    }
//
//    vec3 GeometryMath::ClosestPoint(const OBB& obb, const vec3& point)
//    {
//        vec3 result = obb.origin;
//        vec3 dir = point - obb.origin;
//        for (int i = 0; i < 3; ++i)
//        {
//            vec3 axis =
//                obb.orientation[i * 3];
//            float distance = dot(dir, axis);
//            //Clamp the component on that axis if needed
//            if (distance > obb.size[i])
//            {
//                distance = obb.size[i];
//            }
//            if (distance < -obb.size[i])
//            {
//                distance = -obb.size[i];
//            }
//            //Adjust the final point by the axis and the current projected distance
//            result = result + (axis * distance);
//        }
//
//        return result;
//    }
//
//    bool GeometryMath::PointOnPlane(const vec3& point, const Plane& plane)
//    {
//        return dot(point, plane.normal) - plane.distance == FLT_EPSILON ? true : false;
//    }
//
//    vec3 GeometryMath::ClosestPoint(const Plane& plane, const vec3& point)
//    {
//        float dotFloat = dot(plane.normal, point);
//        float distance = dotFloat - plane.distance;
//        return point - plane.normal * distance;
//    }
//
//    bool GeometryMath::PointOnLine(const vec3& point, const Line& line)
//    {
//        vec3 closest = ClosestPoint(line, point);
//        float distanceSq = ExtraMath::MagSqr(closest - point);
//        // Consider using an epsilon test here!
//        // CMP(distanceSq, 0.0f);
//        return distanceSq == 0.0f;
//    }
//
//    vec3 GeometryMath::ClosestPoint(const Line& line, const vec3& point)
//    {
//        vec3 lVec = line.end - line.start; // Line Vector
//        float t = dot(point - line.start, lVec) /
//            dot(lVec, lVec);
//        t = fmaxf(t, 0.0f); // Clamp to 0
//        t = fminf(t, 1.0f); // Clamp to 1
//        return line.start + lVec * t;
//    }
//
//    bool GeometryMath::PointOnRay(const vec3& point, const Ray& ray)
//    {
//        //If the point is at the origin of the ray, we can return true early:
//        if (point == ray.origin)
//        {
//            return true;
//        }
//        //Find a normal from the point we are testing to the origin of the ray
//        vec3 norm = point - ray.origin;
//        normalize(norm);
//        // We assume the ray direction is normalized
//        //If the normal from the point to the ray and the normal of the ray point in the same direction, 
//        //the result of their dot products will be 1. A point is on a ray only if these vectors point in the same direction:
//        float diff = dot(norm, ray.direction);
//        // If BOTH vectors point in the same direction, 
//        // their dot product (diff) should be 1
//        return diff == 1.0f; // Consider using epsilon!
//
//    }
//
//    vec3 GeometryMath::ClosestPoint(const Ray& ray, const vec3& point)
//    {
//        float t = dot(point - ray.origin, ray.direction);
//        // We assume the direction of the ray is normalized
//        // If for some reason the direction is not normalized
//        // the below division is needed. So long as the ray 
//        // direction is normalized, we don't need this divide
//        // t /= Dot(ray.direction, ray.direction);
//        t = fmaxf(t, 0.0f);
//
//        return vec3(ray.origin + ray.direction * t);
//    }
//
//    void PrintVec3(const vec3& v)
//    {
//        std::cout << v.x << " " << v.y << " " << v.z << std::endl;
//    }
//
//    //glm::vec3 GeometryMath::GetCollisionDepth(const AABB& aabb1, const AABB& aabb2)
//    //{
//    //	vec3 aMin = aabb1.GetMin();
//    //	vec3 aMax = aabb1.GetMax();
//    //	vec3 bMin = aabb2.GetMin();
//    //	vec3 bMax = aabb2.GetMax();
//
//    //	//vec3 min = aMin - bMax;
//    //	//vec3 max = bMin - aMax;
//    //	vec3 depth(0);
//
//    //	if (aMin.x <= bMax.x && aMax.x >= bMin.x) {
//
//    //	}
//
//    //	//if (aMin.x <= bMax.x && aMax.x >= bMin.x) {
//
//
//    //	//}
//    void SwapValue(float& a, float& b) {
//        float t = a;
//        a = b;
//        b = t;
//    }
//
//    int IntersectRayAABB(Ray d, AABB a, float& tmin,vec3& point)
//    {
//    	tmin = 0.0f;                 // set to -FLT_MAX to get first hit on line
//        float tmax = FLT_MAX;        // set to max distance ray can travel (for segment)
//        // For all three slabs
//        
//        for (int i = 0; i < 3;i++)
//            if (abs(d.direction[i]) < FLT_EPSILON) {
//                // Ray is parallel to slab. No hit if origin not within slab
//                if (d.origin[i] < a.GetMin()[i] || d.origin[i] > a.GetMax()[i]) return 0;
//            }
//            else {
//                // Compute intersection t value of ray with near and far plane of slab
//                float ood = 1.0f / d.direction[i];
//                    float t1 = (a.GetMin()[i] - d.origin[i]) * ood;
//                    float t2 = (a.GetMax()[i] - d.origin[i]) * ood;
//                    // Make t1 be intersection with near plane, t2 with far plane
//                    if (t1 > t2) SwapValue(t1, t2);
//                // Compute the intersection of slab intersection intervals
//                tmin = max(tmin, t1);
//                tmax = min(tmax, t2);
//                // Exit with no collision as soon as slab intersection becomes empty
//                if (tmin > tmax) return 0;
//            }
//
//    
//    // Ray intersects all 3 slabs. Return point (q) and intersection t value (tmin)
//        point = d.origin + d.direction * tmin;
//    return 1;
//    }
//
//    bool GeometryMath::Raycast(Ray d, const AABB a, float& tmin, vec3& point)
//    {
//
//        tmin = 0.0f;                 // set to -FLT_MAX to get first hit on line
//        float tmax = FLT_MAX;        // set to max distance ray can travel (for segment)
//        // For all three slabs
//
//        for (int i = 0; i < 3; i++)
//            if (abs(d.direction[i]) < FLT_EPSILON) {
//                // Ray is parallel to slab. No hit if origin not within slab
//                if (d.origin[i] < a.GetMin()[i] || d.origin[i] > a.GetMax()[i]) return false;
//            }
//            else {
//                // Compute intersection t value of ray with near and far plane of slab
//                float ood = 1.0f / d.direction[i];
//                float t1 = (a.GetMin()[i] - d.origin[i]) * ood;
//                float t2 = (a.GetMax()[i] - d.origin[i]) * ood;
//                // Make t1 be intersection with near plane, t2 with far plane
//                if (t1 > t2) SwapValue(t1, t2);
//                // Compute the intersection of slab intersection intervals
//                tmin = max(tmin, t1);
//                tmax = min(tmax, t2);
//                // Exit with no collision as soon as slab intersection becomes empty
//                if (tmin > tmax) return false;
//            }
//
//        // Ray intersects all 3 slabs. Return point (q) and intersection t value (tmin)
//        point = d.origin + d.direction * tmin;
//        return true;
//    }
//
//    //	//return (aMin.x <= bMax.x && aMax.x >= bMin.x) &&
//    //	//	(aMin.y <= bMax.y && aMax.y >= bMin.y) &&
//    //	//	(aMin.z <= bMax.z && aMax.z >= bMin.z);
//    //	//return glm::vec3();
//    //}
//    bool GeometryMath::SphereSphere(Sphere s1, Sphere s2)
//    {
//        float radiiSum = s1.radius + s2.radius;
//        float sqDistance = ExtraMath::MagSqr(s1.origin - s2.origin);
//        return sqDistance < radiiSum * radiiSum;
//    }
//
//    bool GeometryMath::AABBAABB(const AABB& aabb1, const AABB& aabb2)
//    {
//        float tFirst = 0.0f;
//        float tLast = 1.0f;
//
//        for (int i = 0; i < 3; i++)
//        {
//        }
//
//        vec3 aMin = aabb1.GetMin();
//        vec3 aMax = aabb1.GetMax();
//        vec3 bMin = aabb2.GetMin();
//        vec3 bMax = aabb2.GetMax();
//        return (aMin.x <= bMax.x && aMax.x >= bMin.x) &&
//            (aMin.y <= bMax.y && aMax.y >= bMin.y) &&
//            (aMin.z <= bMax.z && aMax.z >= bMin.z);
//    }
//
//    bool GeometryMath::SphereAABB(const Sphere& sphere, const AABB& aabb)
//    {
//        vec3 closestPoint = ClosestPoint(aabb, sphere.origin);
//        float distSq = ExtraMath::MagSqr(sphere.origin - closestPoint);
//        float radiusSq = sphere.radius * sphere.radius;
//        return distSq < radiusSq;
//
//    }
//
//    bool GeometryMath::Collision(const Sphere& s1, const Sphere& s2)
//    {
//        return SphereSphere(s1, s2);
//    }
//
//    bool GeometryMath::Collision(const AABB& aabb1, const AABB& aabb2)
//    {
//        return AABBAABB(aabb1, aabb2);
//    }
//
//    bool GeometryMath::Collision(const Sphere& sphere, const AABB& aabb)
//    {
//        return SphereAABB(sphere, aabb);
//    }
//
//    bool GeometryMath::Collision(const AABB& aabb, const Sphere& sphere)
//    {
//        return SphereAABB(sphere, aabb);
//    }
//}
