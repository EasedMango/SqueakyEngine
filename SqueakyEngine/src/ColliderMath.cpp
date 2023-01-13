#include "ColliderMath.h"

#include <iostream>
#include <ostream>
#include <glm/geometric.hpp>
#include <glm/vector_relational.hpp>

#include "Components/PhysicsBody.h"
#include "Components/Physics/Plane.h"
#include "Components/Physics/Sphere.h"
#include "Components/Physics/Ray.h"
#include "Components/Physics/AABB.h"
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




}

glm::vec4 ColliderMath::QuadraticEqn(const Ray& ray, const Sphere& sphere)
{

	float a = glm::dot( ray.dir,ray.dir);
	float b = 2 * glm::dot((ray.start - sphere.pos),(ray.dir));
	float c = glm::dot((ray.start - sphere.pos),(ray.start - sphere.pos)) - powf(sphere.radius, 2);
	float d = powf(b, 2) - 4 * a * c;

	return {a, b, c, d};
}




bool ColliderMath::RayAABCollisionDetected(const Ray& ray, const AABB& box)
{

	return (0 <= ray.dir.x <= -box.planes[3].w && 0 <= ray.dir.y <= -box.planes[4].w && 0 <= ray.dir.z <= -box.planes[5].w)
		? true : false;

}

glm::vec3 ColliderMath::RayAABCollisionPoint(const Ray& ray, const AABB& box)
{
	if (RayAABCollisionDetected(ray, box)) {

		glm::vec3 px, py, pz;

		//Check  x
		if (ray.dir.x == 0) {
			px = glm::vec3(FLT_EPSILON, FLT_EPSILON, FLT_EPSILON);
			std::cout << "x = 0" << std::endl;
		}
		else if (ray.dir.x > 0) {
			float t = (box.planes[0].w - ray.start.x) / ray.dir.x;
			px = ray.CurrentPosition(t);
			std::cout << "x > 0" << std::endl;
		}
		else if (ray.dir.x < 0) {
			float t = (box.planes[3].w - ray.start.x) / ray.dir.x;
			px = ray.CurrentPosition(t);
			std::cout << "x < 0" << std::endl;
		}

		//return x if closest
		if (glm::all(glm::lessThanEqual(glm::vec3(0, 0, 0), px)) && glm::all(glm::lessThanEqual(px, glm::vec3(-box.planes[3].w, -box.planes[4].w, -box.planes[5].w)))) {
			std::cout << "return px" << std::endl;
			return px;
		}

		//else check y
		else if (ray.dir.y == 0) {
			py = glm::vec3(FLT_EPSILON, FLT_EPSILON, FLT_EPSILON);
			std::cout << "y = 0" << std::endl;
		}

		else if (ray.dir.y > 0) {
			float t = (box.planes[1].w - ray.start.y) / ray.dir.y;
			py = ray.CurrentPosition(t);
			std::cout << "y > 0" << std::endl;

		}
		else if (ray.dir.y < 0) {
			float t = (box.planes[4].w - ray.start.y) / ray.dir.y;
			py = ray.CurrentPosition(t);
			std::cout << "y < 0" << std::endl;
		}
	
		
		//return y if closest
		if (glm::all(glm::lessThanEqual(glm::vec3(0, 0, 0), py)) && glm::all(glm::lessThanEqual( py, glm::vec3(-box.planes[3].w, -box.planes[4].w, -box.planes[5].w)))) {
			std::cout << "return py" << std::endl;
			return glm::vec3(py.x, py.y, py.z);
		}

		//else check z 
		else if (ray.dir.z == 0) {
			pz = glm::vec3(FLT_EPSILON, FLT_EPSILON, FLT_EPSILON);
			std::cout << "z = 0" << std::endl;
		}
		else if (ray.dir.z > 0) {
			float t = (box.planes[2].w - ray.start.z) / ray.dir.z;
			pz = ray.CurrentPosition(t);
			std::cout << "z > 0" << std::endl;
		}
		else if (ray.dir.z < 0) {
			float t = (box.planes[5].w - ray.start.z) / ray.dir.z;
			pz = ray.CurrentPosition(t);
			std::cout << "z < 0" << std::endl;
		}

		//return y if closest 
		if (glm::all(glm::lessThanEqual(glm::vec3(0, 0, 0), pz)) && glm::all(glm::lessThanEqual(pz, glm::vec3(-box.planes[3].w, -box.planes[4].w, -box.planes[5].w)))) {
			std::cout << "return pz" << std::endl;
			return pz;
		}



	}
	return { FLT_EPSILON, FLT_EPSILON, FLT_EPSILON };
}

bool ColliderMath::SphereSphereCollisionDetected(const PhysicsBody& p1, const PhysicsBody& p2)
{
	const float distance = glm::length(p1.GetPos() - p2.GetPos());
	const float radiusSum = p1.GetRadius() + p2.GetRadius();
	return distance < radiusSum ? true : false;
}

void ColliderMath::SphereSphereCollisionResponse(PhysicsBody& phyObj1, PhysicsBody& phyObj2)
{
	if (SphereSphereCollisionDetected(phyObj1, phyObj2)) {

		float e = 1.0f;// e > 1 ? e = 1 : e < 0 ? e = 0 : e;

		//((m1*v1i)+(m2*v2i)+m1*(e*(v1i-v2i)))/(m1+m2)
		/*Vec3 vf0 = (
			((phyObj1.GetMass() * phyObj1.GetVelocity()) +
			(phyObj2.GetMass() * phyObj2.GetVelocity())) +
			((phyObj1.GetMass() * e) * (phyObj1.GetVelocity() - phyObj2.GetVelocity()))) /
			(phyObj1.GetMass() + phyObj2.GetMass());*/
		glm::vec3 N = glm::normalize(phyObj1.GetPos() - phyObj2.GetPos());
		float p1 = (glm::dot(-phyObj1.GetVel(), N));
		float p2 = (glm::dot(-phyObj2.GetVel(), N));


		//float vf1 = (((phyObj1.GetMass() * p1) + (phyObj2.GetMass() * p2))
		//	+ ((phyObj2.GetMass() * e) * (p2 - p1))) / (phyObj2.GetMass() + phyObj1.GetMass());
		float vf1 = ((((phyObj1.GetMass() * p1) + (phyObj2.GetMass() * p2))
			+ ((phyObj2.GetMass() * e * p2) - (phyObj2.GetMass() * e * p1)))) / (phyObj1.GetMass() + phyObj2.GetMass());
		//float vf2 = (((phyObj1.GetMass() * p1) + (phyObj2.GetMass() * p2))
		//	+ ((phyObj1.GetMass() * e) * (p1 - p2))) / (phyObj2.GetMass() + phyObj1.GetMass());
		float vf2 = ((((phyObj1.GetMass() * p1) + (phyObj2.GetMass() * p2))
			+ ((phyObj1.GetMass() * e * p1) - (phyObj1.GetMass() * e * p2)))) / (phyObj1.GetMass() + phyObj2.GetMass());



		phyObj1.SetVel((vf2 - p2) * N);
		phyObj2.SetVel((vf1 - p1) * N);


	}
}

