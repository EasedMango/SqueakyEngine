#include "GeometryMath.h"
#include "ExtraMath.h"
using namespace glm;
namespace Geometry {
	bool Geometry::GeometryMath::PointInSphere(const vec3& point, const Sphere& sphere)
	{
		//Find the square magnitude of the line between the sphere center and test point as well as the square radius of the sphere:
		float magSq = ExtraMath::MagSqr(point - sphere.origin);
		//Compare the square magnitude to the square radius. If the square magnitude is less, the point is inside the sphere:
		float radSq = sphere.radius * sphere.radius;
		return magSq < radSq;
	}

	vec3 GeometryMath::ClosestPoint(const Sphere& sphere, const vec3& point)
	{
		//Find a normalized vector from the center of the sphere to the test point :
		vec3 sphereToPoint = point - sphere.origin;
		normalize(sphereToPoint);
		//Resize the normalized vector to the size of the radius :
		sphereToPoint = sphereToPoint * sphere.radius;
		//Return the resized vector offset by the position of the sphere :
		return sphereToPoint + sphere.origin;
	}

	bool GeometryMath::PointInAABB(const vec3& point, const AABB& aabb)
	{
		vec3 min = aabb.GetMin();
		vec3 max = aabb.GetMax();
		//The shapes do not intersect if any component of the test point is smaller/larger than the respective component of the min/max point of the AABB :
		if (point.x < min.x || point.y < min.y || point.z < min.z) {
			return false;
		}
		if (point.x > max.x || point.y > max.y || point.z > max.z) {
			return false;
		}

		return true;
	}


	vec3 GeometryMath::ClosestPoint(const AABB& aabb, const vec3& point)
	{
		vec3 result = point;
		vec3 min = aabb.GetMin();
		vec3 max = aabb.GetMax();
		result.x = (result.x < min.x) ? min.x : result.x;
		result.y = (result.y < min.x) ? min.y : result.y;
		result.z = (result.z < min.x) ? min.z : result.z;
		result.x = (result.x > max.x) ? max.x : result.x;
		result.y = (result.y > max.x) ? max.y : result.y;
		result.z = (result.z > max.x) ? max.z : result.z;

		return result;
	}

	bool GeometryMath::PointInOBB(const vec3& point, const OBB& obb)
	{
		//We are going to move the point relative to the oriented bounding box by subtracting the box position from the point:
		vec3 dir = point - obb.origin;
		//This loop will run three times. Iteration 0 is the X axis, iteration 1 is the Y axis, and iteration 2 is the Z axis. 
		//We will project the point onto each of the local axes of the box and compare the distance to the extent of the box on that axis:
		for (int i = 0; i < 3; ++i) {
			vec3 axis =
				obb.orientation[i * 3];
			// Next we project the relative point onto that axisand record how far from the origin of the box the projection is :
			float distance = dot(dir, axis);
			//If the distance is greater than the extent of the box, or less than the negative extent of the box, the point is not inside the box
			if (distance > obb.size[i]) {
				return false;
			}
			if (distance < -obb.size[i]) {
				return false;
			}
		}

		return true;


	}

	vec3 GeometryMath::ClosestPoint(const OBB& obb, const vec3& point)
	{
		vec3 result = obb.origin;
		vec3 dir = point - obb.origin;
		for (int i = 0; i < 3; ++i) {
			vec3 axis =
				obb.orientation[i * 3];
			float distance = dot(dir, axis);
			//Clamp the component on that axis if needed
			if (distance > obb.size[i]) {
				distance = obb.size[i];
			}
			if (distance < -obb.size[i]) {
				distance = -obb.size[i];
			}
			//Adjust the final point by the axis and the current projected distance
			result = result + (axis * distance);
		}

		return result;
	}

	bool GeometryMath::PointOnPlane(const vec3& point, const Plane& plane)
	{
		return dot(point, plane.normal) - plane.distance == FLT_EPSILON ? true : false;
	}

	vec3 GeometryMath::ClosestPoint(const Plane& plane, const vec3& point)
	{
		float dotFloat = dot(plane.normal, point);
		float distance = dotFloat - plane.distance;
		return point - plane.normal * distance;
	}

	bool GeometryMath::PointOnLine(const vec3& point, const Line& line)
	{
		return false;
	}

	vec3 GeometryMath::ClosestPoint(const Line& line, const vec3& point)
	{
		return vec3();
	}
}