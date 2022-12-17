#include "Geometry.h"

#include <iostream>


//Raycasts
int Geometry::IntersectRaySphere(glm::vec3 p, glm::vec3 d, Geometry::Sphere s, float& t, glm::vec3& q)
{
	glm::vec3 m = p - s.center;
	float b = glm::dot(m, d);
	float c = glm::dot(m, m) - s.radius * s.radius;
	// Exit if r’s origin outside s (c > 0) and r pointing away from s (b > 0)
	if (c > 0.0f && b > 0.0f) return 0;
	float discr = b * b - c;
	// A negative discriminant corresponds to ray missing sphere
	if (discr < 0.0f) return 0;
	// Ray now found to intersect sphere, compute smallest t value of intersection
	t = -b - sqrt(discr);
	// If t is negative, ray started inside sphere so clamp t to zero
	if (t < 0.0f) t = 0.0f;
	q = p + t * d;
	return 1;
}
int Geometry::TestRaySphere(glm::vec3 p, glm::vec3 d, Geometry::Sphere s)
{
	glm::vec3 m = p - s.center;
	float c = glm::dot(m, m) - s.radius * s.radius;
	// If there is definitely at least one real root, there must be an intersection
	if (c <= 0.0f) return 1;
	float b = glm::dot(m, d);
	// Early exit if ray origin outside sphere and ray pointing away from sphere
	if (b > 0.0f) return 0;
	float disc = b * b - c;
	// A negative discriminant corresponds to ray missing sphere
	if (disc < 0.0f) return 0;
	// Now ray must hit sphere
	return 1;
}

int Geometry::IntersectRayAABB(glm::vec3 p, glm::vec3 d, AABB a, float& tmin, glm::vec3& q)
{
	tmin = 0.0f;                 // set to -FLT_MAX to get first hit on line
	float tmax = FLT_MAX;        // set to max distance ray can travel (for segment)
	// For all three slabs

	for (int i = 0; i < 3; i++)
		if (abs(d[i]) < FLT_EPSILON) {
			// Ray is parallel to slab. No hit if origin not within slab
			if (p[i] < a.GetMin()[i] || p[i] > a.GetMax()[i]) return 0;
		}
		else {
			// Compute intersection t value of ray with near and far plane of slab
			float ood = 1.0f / d[i];
			float t1 = (a.GetMin()[i] - p[i]) * ood;
			float t2 = (a.GetMax()[i] - p[i]) * ood;
			// Make t1 be intersection with near plane, t2 with far plane
			if (t1 > t2) SwapValue(t1, t2);
			// Compute the intersection of slab intersection intervals
			tmin = glm::max(tmin, t1);
			tmax = glm::min(tmax, t2);
			// Exit with no collision as soon as slab intersection becomes empty
			if (tmin > tmax) return 0;
		}


	// Ray intersects all 3 slabs. Return point (q) and intersection t value (tmin)
	q = p + d * tmin;
	return 1;
}


// Basic Intercetion Tests


bool Geometry::TestAABBAABB(AABB a, AABB b)
{
	if (abs(a.center[0] - b.center[0]) > (a.radius[0] + b.radius[0])) return false;
	if (abs(a.center[1] - b.center[1]) > (a.radius[1] + b.radius[1])) return false;
	if (abs(a.center[2] - b.center[2]) > (a.radius[2] + b.radius[2])) return false;
	return true;

}

int Geometry::TestSphereSphere(Sphere a, Sphere b)
{
	// Calculate squared distance between centers
	glm::vec3 d = a.center - b.center;
	float dist2 = glm::dot(d, d);
	// Spheres intersect if squared distance is less than squared sum of radii
	float radiusSum = a.radius + b.radius;
	return dist2 <= radiusSum * radiusSum;
}


bool Geometry::RaySphereCollisionDetected(const Ray& ray, const Sphere& sphere)
{

	return QuadraticEqn(ray, sphere).w < 0 ? false : true;

}

Geometry::RayResults Geometry::RaySphereCollisionPoint(const Ray& ray, const Sphere& sphere)
{
	std::cout << "W: " << QuadraticEqn(ray, sphere).w << std::endl;
	if (Geometry::RaySphereCollisionDetected(ray, sphere)) {
		const glm::vec4 quad = QuadraticEqn(ray, sphere);
		float t = 0;
		//t1= -B-sqrt(Discriminant)/2A
		float t1 = (-quad.y - sqrtf(quad.w)) / (2 * quad.x);
		//std::cout << t1 << std::endl;
		//t2= -B+sqrt(Discriminant)/2A
		float t2 = (-quad.y + sqrtf(quad.w)) / (2 * quad.x);
		//std::cout << t2 << std::endl;


		fminf(fabsf(t1), fabsf(t2)) == fabsf(t1) ? t = t1 : t = t2;



		return (Geometry::RayResults(t, ray.CurrentPosition(t)));
	}
	return (Geometry::RayResults(FLT_EPSILON, { FLT_EPSILON, FLT_EPSILON, FLT_EPSILON }));



}

glm::vec4 Geometry::QuadraticEqn(const Ray& ray, const Sphere& sphere)
{

	float a = glm::dot(ray.dir, (ray.dir));
	float b = 2 * glm::dot((ray.start - sphere.center), (ray.dir));
	float c = glm::dot((ray.start - sphere.center), (ray.start - sphere.center)) - powf(sphere.radius, 2);
	float d = powf(b, 2) - 4 * a * c;

	return { a, b, c, d };
}

int Geometry::TestOBBOBB(OBB& a, OBB& b)
{
	float ra, rb;
	glm::mat4 R, AbsR;

	// Compute rotation matrix expressing b in a’s coordinate frame
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			R[i][j] = glm::dot(a.u[i], b.u[j]);

	// Compute translation vector t
	glm::vec3 t = b.c - a.c;
	// Bring translation into a’s coordinate frame
	t = glm::vec3(glm::dot(t, a.u[0]), glm::dot(t, a.u[1]), glm::dot(t, a.u[2]));

	// Compute common subexpressions. Add in an epsilon term to
	// counteract arithmetic errors when two edges are parallel and
	// their cross product is (near) null (see text for details)
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			AbsR[i][j] = abs(R[i][j]) + FLT_EPSILON;

	// Test axes L = A0, L = A1, L = A2
	for (int i = 0; i < 3; i++) {
		ra = a.e[i];
		rb = b.e[0] * AbsR[i][0] + b.e[1] * AbsR[i][1] + b.e[2] * AbsR[i][2];
		if (abs(t[i]) > ra + rb) return 0;
	}

	// Test axes L = B0, L = B1, L = B2
	for (int i = 0; i < 3; i++) {
		ra = a.e[0] * AbsR[0][i] + a.e[1] * AbsR[1][i] + a.e[2] * AbsR[2][i];
		rb = b.e[i];
		if (abs(t[0] * R[0][i] + t[1] * R[1][i] + t[2] * R[2][i]) > ra + rb) return 0;
	}

	// Test axis L = A0 x B0
	ra = a.e[1] * AbsR[2][0] + a.e[2] * AbsR[1][0];
	rb = b.e[1] * AbsR[0][2] + b.e[2] * AbsR[0][1];
	if (abs(t[2] * R[1][0] - t[1] * R[2][0]) > ra + rb) return 0;

	// Test axis L = A0 x B1
	ra = a.e[1] * AbsR[2][1] + a.e[2] * AbsR[1][1];
	rb = b.e[0] * AbsR[0][2] + b.e[2] * AbsR[0][0];
	if (abs(t[2] * R[1][1] - t[1] * R[2][1]) > ra + rb) return 0;

	// Test axis L = A0 x B2
	ra = a.e[1] * AbsR[2][2] + a.e[2] * AbsR[1][2];
	rb = b.e[0] * AbsR[0][1] + b.e[1] * AbsR[0][0];
	if (abs(t[2] * R[1][2] - t[1] * R[2][2]) > ra + rb) return 0;

	// Test axis L = A1 x B0
	ra = a.e[0] * AbsR[2][0] + a.e[2] * AbsR[0][0];
	rb = b.e[1] * AbsR[1][2] + b.e[2] * AbsR[1][1];
	if (abs(t[0] * R[2][0] - t[2] * R[0][0]) > ra + rb) return 0;

	// Test axis L = A1 x B1
	ra = a.e[0] * AbsR[2][1] + a.e[2] * AbsR[0][1];
	rb = b.e[0] * AbsR[1][2] + b.e[2] * AbsR[1][0];
	if (abs(t[0] * R[2][1] - t[2] * R[0][1]) > ra + rb) return 0;

	// Test axis L = A1 x B2
	ra = a.e[0] * AbsR[2][2] + a.e[2] * AbsR[0][2];
	rb = b.e[0] * AbsR[1][1] + b.e[1] * AbsR[1][0];
	if (abs(t[0] * R[2][2] - t[2] * R[0][2]) > ra + rb) return 0;

	// Test axis L = A2 x B0
	ra = a.e[0] * AbsR[1][0] + a.e[1] * AbsR[0][0];
	rb = b.e[1] * AbsR[2][2] + b.e[2] * AbsR[2][1];
	if (abs(t[1] * R[0][0] - t[0] * R[1][0]) > ra + rb) return 0;

	// Test axis L = A2 x B1
	ra = a.e[0] * AbsR[1][1] + a.e[1] * AbsR[0][1];
	rb = b.e[0] * AbsR[2][2] + b.e[2] * AbsR[2][0];
	if (abs(t[1] * R[0][1] - t[0] * R[1][1]) > ra + rb) return 0;

	// Test axis L = A2 x B2
	ra = a.e[0] * AbsR[1][2] + a.e[1] * AbsR[0][2];
	rb = b.e[0] * AbsR[2][1] + b.e[1] * AbsR[2][0];
	if (abs(t[1] * R[0][2] - t[0] * R[1][2]) > ra + rb) return 0;

	// Since no separating axis is found, the OBBs must be intersecting
	return 1;
}


// Moving Intercetion Tests
bool Geometry::IntersectMovingAABBAABB(AABB a, AABB b, glm::vec3 va, glm::vec3 vb, float& tfirst, float& tlast)
{
	// Exit early if ‘a’ and ‘b’ initially overlapping
	if (Geometry::TestAABBAABB(a, b)) {
		tfirst = tlast = 0.0f;
		return true;
	}
	// Use relative velocity; effectively treating ‘a’ as stationary
	glm::vec3 v = vb - va;
	// Initialize times of first and last contact
	tfirst = 0.0f;
	tlast = 1.0f;

	// For each axis, determine times of first and last contact, if any
	for (int i = 0; i < 3; i++) {
		if (v[i] < 0.0f) {
			if (b.GetMax()[i] < a.GetMin()[i]) return false;   // Nonintersecting and moving apart
			if (a.GetMax()[i] < b.GetMin()[i]) tfirst = glm::max((a.GetMax()[i] - b.GetMin()[i]) / v[i], tfirst);
			if (b.GetMax()[i] > a.GetMin()[i]) tlast = glm::min((a.GetMin()[i] - b.GetMax()[i]) / v[i], tlast);
		}
		if (v[i] > 0.0f) {
			if (b.GetMin()[i] > a.GetMax()[i]) return false;   // Nonintersecting and moving apart
			if (b.GetMax()[i] < a.GetMin()[i]) tfirst = glm::max((a.GetMin()[i] - b.GetMax()[i]) / v[i], tfirst);
			if (a.GetMax()[i] > b.GetMin()[i]) tlast = glm::min((a.GetMax()[i] - b.GetMin()[i]) / v[i], tlast);
		}

		// No overlap possible iftime offirst contact occurs after time oflast contact
		if (tfirst > tlast) return false;
	}
	return true;
}







int Geometry::TestMovingSphereSphere(Sphere s0, Sphere s1, glm::vec3 v0, glm::vec3 v1, float& t)
{
	//glm::vec3 s = s1.center - s0.center;   // glm::vec3 between sphere centers
	//glm::vec3 v = v1 - v0;       // Relative motion of si with respect to stationary s0
	//float r = s1.radius + s0.radius;    // Sum of sphere radii
	//float c = glm::dot(s, s) - r * r;
	//if (c < 0.0f) {
	//	// Spheres initially overlapping so exit directly
	//	t = 0.0f;
	//	return 1;
	//}
	//float a = glm::dot(v, v);
	//if (a < FLT_EPSILON) return 0; // Spheres not moving relative each other
	//float b = glm::dot(v, s);
	//if (b >= 0.0f) return 0;   // Spheres not moving towards each other
	//float d = b * b-a * c;
	//if (d < 0.0f) return 0;    // No real-valued root, spheres do not intersect

	//t = (-b - sqrt(d)) / a;
	//return 1;

	// Expand sphere si by the radius of s0
	s1.radius += s0.radius;
	// Subtract movement of s1 from both sO and s1, making s1 stationary
	glm::vec3 v = v0 - v1;
	// Can now test directed segment s = sO.c + tv, v = (v0–v1)/||v0–v1|| against
	// the expanded sphere for intersection
	glm::vec3 q;
	float vlen = glm::length(v);
	if (IntersectRaySphere(s0.center, v / vlen, s1, t, q)) {
		return t <= vlen;
	}
	return 0;
}

glm::vec3 Geometry::Corner(AABB b, int n)
{
	glm::vec3 p;
	p.x = ((n & 1) ? b.GetMax().x : b.GetMin().x);
	p.y = ((n & 2) ? b.GetMax().y : b.GetMin().y);
	p.z = ((n & 4) ? b.GetMax().z : b.GetMin().z);
	return p;
}


void Geometry::SwapValue(float& a, float& b)
{
	float t = a;
	a = b;
	b = t;
}

Geometry::Ray::Ray(const glm::vec3& start_, const glm::vec3& dir_) : start(start_), dir(dir_)
{
	dir = glm::normalize(dir);
}

Geometry::Ray::~Ray()
{
}

glm::vec3 Geometry::Ray::CurrentPosition(const float& t) const
{
	return start + dir * t;
}
