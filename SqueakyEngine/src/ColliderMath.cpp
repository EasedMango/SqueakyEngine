#include "ColliderMath.h"

#include <algorithm>
#include <iostream>
#include <ostream>
#include <glm/geometric.hpp>
#include <glm/vector_relational.hpp>

#include "Renderer.h"
#include "Components/PhysicsBody.h"
#include "Components/Physics/Plane.h"
#include "Components/Physics/Sphere.h"
#include "Components/Physics/Ray.h"
#include "Components/Physics/AABB.h"
#include "Components/Physics/OBB.h"

bool ColliderMath::RaySphereCollisionDetected(const Ray& ray, const Sphere& sphere)
{

	return QuadraticEqn(ray, sphere).w < 0 ? false : true;

}

glm::vec3 ColliderMath::RaySphereCollisionPoint(const Ray& ray, const Sphere& sphere)
{

	if (RaySphereCollisionDetected(ray, sphere)) {
		glm::vec4 quad = QuadraticEqn(ray, sphere);
		float t = 0;
		//t1= -B-sqrt(Discriminant)/2A
		float t1 = (-quad.y - sqrtf(quad.w)) / (2 * quad.x);
		//std::cout << t1 << std::endl;
		//t2= -B+sqrt(Discriminant)/2A
		float t2 = (-quad.y + sqrtf(quad.w)) / (2 * quad.x);
		//std::cout << t2 << std::endl;


		fminf(fabsf(t1), fabsf(t2)) == fabsf(t1) ? t = t1 : t = t2;



		return (ray.CurrentPosition(t));
	}
	return { FLT_EPSILON, FLT_EPSILON, FLT_EPSILON };



}

glm::vec4 ColliderMath::QuadraticEqn(const Ray& ray, const Sphere& sphere)
{

	float a = glm::dot(ray.dir, ray.dir);
	float b = 2 * glm::dot((ray.start - sphere.pos), (ray.dir));
	float c = glm::dot((ray.start - sphere.pos), (ray.start - sphere.pos)) - powf(sphere.radius, 2);
	float d = powf(b, 2) - 4 * a * c;

	return { a, b, c, d };
}



ColliderMath::CollisionResult ColliderMath::OBBOBBCollision(const OBB& box1, const OBB& box2)
{
	CollisionResult result;
	result.collide = false;
	result.penetrationDepth = FLT_MAX;
	result.closestPoint = glm::vec3(0);

	// Compute the rotation matrix that transforms box2 into box1's space
	glm::mat3 R = glm::transpose(box1.rotation) * box2.rotation;
	glm::vec3 T = box2.center - box1.center;
	T = box1.rotation * T;

	// Test the three major axes of box1
	for (int i = 0; i < 3; i++) {
		float r1 = box1.extents[i];
		float r2 = box2.extents[0] * fabs(R[i][0]) + box2.extents[1] * fabs(R[i][1]) + box2.extents[2] * fabs(R[i][2]);
		if (fabs(T[i]) > r1 + r2) return result;
	}

	// Test the three major axes of box2
	for (int i = 0; i < 3; i++) {
		float r1 = box1.extents[0] * fabs(R[0][i]) + box1.extents[1] * fabs(R[1][i]) + box1.extents[2] * fabs(R[2][i]);
		float r2 = box2.extents[i];
		if (fabs(T[0] * R[0][i] + T[1] * R[1][i] + T[2] * R[2][i]) > r1 + r2) return result;
	}

	// Test the nine edge cross-axes of box1 and box2
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			float r1 = box1.extents[i] * fabs(R[j][i]) + box1.extents[j] * fabs(R[i][i]);
			float r2 = box2.extents[i] * fabs(R[i][j]) + box2.extents[j] * fabs(R[i][i]);
			if (fabs(T[j] * R[i][j] - T[i] * R[j][i]) > r1 + r2) return result;
		}
	}

	// Since no separating axis is found, the OBBs must be intersecting
	result.collide = true;

	// Compute the penetration
		//depthand closest point on the collision surface
		float minPenetration = FLT_MAX;
	glm::vec3 normal;


		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				float r1 = box1.extents[i];
				float r2 = box2.extents[0] * fabs(R[i][0]) + box2.extents[1] * fabs(R[i][1]) + box2.extents[2] * fabs(R[i][2]);
				float axisLength = fabs(T[i]);
				float penetration = r1 + r2 - axisLength;
				if (penetration < minPenetration) {
					minPenetration = penetration;
					normal = box1.rotation * glm::vec3(i == 0 ? 1 : 0, i == 1 ? 1 : 0, i == 2 ? 1 : 0);
					if (T[i] < 0) normal = -normal;
				}
			}
		}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			float r1 = box1.extents[0] * fabs(R[0][i]) + box1.extents[1] * fabs(R[1][i]) + box1.extents[2] * fabs(R[2][i]);
			float r2 = box2



			
				.extents[i];
			float axisLength = fabs(T[0] * R[0][i] + T[1] * R[1][i] + T[2] * R[2][i]);
			float penetration = r1 + r2 - axisLength;
			if (penetration < minPenetration) {
				minPenetration = penetration;
				normal = box1.rotation * glm::vec3(R[0][i], R[1][i], R[2][i]);
				if (T[0] * R[0][i] + T[1] * R[1][i] + T[2] * R[2][i] < 0) normal = -normal;
			}
		}
	}

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				float r1 = box1.extents[i] * fabs(R[j][i]) + box1.extents[j] * fabs(R[i][i]);
				float r2 = box2.extents[i] * fabs(R[i][j]) + box2.extents[j] * fabs(R[i][i]);
				float axisLength = fabs(T[j] * R[i][j] - T[i] * R[j][i]);
				float penetration = r1 + r2 - axisLength;
				if (penetration < minPenetration) {
					minPenetration = penetration;
					normal = glm::cross(box1.rotation * glm::vec3(i == 0 ? 1 : 0, i == 1 ? 1 : 0, i == 2 ? 1 : 0),
						box2.rotation * glm::vec3(j == 0 ? 1 : 0, j == 1 ? 1 : 0, j == 2 ? 1 : 0));
					if (T[j] * R[i][j] - T[i] * R[j][i] < 0) normal = -normal;
				}
			}
		}

	result.penetrationDepth = minPenetration;
	result.closestPoint = box1.center + (box1.rotation * (T - normal * (minPenetration / 2)));
	return result;
}
ColliderMath::CollisionResult ColliderMath::OBBSphereCollision(const OBB& obb, const Sphere& sphere) {
	CollisionResult result;
	result.collide = false;

	// Transform the sphere's center into the OBB's local space
	glm::vec3 sphereCenter = glm::inverse(obb.rotation) * (sphere.pos - obb.center);

	// Clamp the sphere's center to the nearest point on the OBB
	glm::vec3 closestPoint = sphereCenter;
	closestPoint.x = glm::clamp(closestPoint.x, -obb.extents.x, obb.extents.x);
	closestPoint.y = glm::clamp(closestPoint.y, -obb.extents.y, obb.extents.y);
	closestPoint.z = glm::clamp(closestPoint.z, -obb.extents.z, obb.extents.z);

	// Check if the closest point is inside the sphere
	float distance = glm::length(closestPoint - sphereCenter);
	if (distance <= sphere.radius) {
		result.collide = true;
		result.penetrationDepth = sphere.radius - distance;
		result.closestPoint = obb.rotation * closestPoint + obb.center;
	}

	return result;
}
ColliderMath::CollisionResult ColliderMath::SphereSphereCollision(const Sphere& sphere1, const Sphere& sphere2) {
	ColliderMath::CollisionResult result{};
	// Vector from center of sphere1 to center of sphere2
	glm::vec3 distance = sphere2.pos - sphere1.pos;
	float distanceSquared = glm::length(distance);
	float radiusSum = sphere1.radius + sphere2.radius;
	if (distanceSquared < radiusSum * radiusSum) {
		// The spheres are colliding
		result.collide = true;
		// Normalize the distance vector
		distance = glm::normalize(distance);
		result.closestPoint = sphere1.pos + distance * sphere1.radius;
		result.penetrationDepth = radiusSum - sqrt(distanceSquared);
	}
	else {
		// The spheres are not colliding
		result.collide = false;
	}
	return result;
}




