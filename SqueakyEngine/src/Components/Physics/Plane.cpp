#include "Plane.h"

#include <iostream>
#include <ostream>
#include <glm/geometric.hpp>

#include "Ray.h"

Plane::Plane(glm::vec4 plane_)
{
	x = plane_.x;
	y = plane_.y;
	z = plane_.z;
	w = plane_.w;
}
Plane::Plane() 
{}

Plane::Plane(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2) 
{
	glm::vec3 e1 = v1 - v0;
	glm::vec3 e2 = v2 - v1;
	glm::vec3 n = glm::normalize(glm::cross(e1, e2));

	const float d = glm::dot(-n, (v0));


	std::cout << n.x << " " <<
		n.y << " " <<
		n.z << " " <<
		d << std::endl;
	x = n.x;
	y = n.y;
	z = n.z;
	w = d;

	//glm::vec4 d = 

}

glm::vec3 const Plane::IntersectionPoint(const Ray& ray)
{

	glm::vec3 n(x, y, z);//planes normal
	//float d = plane.w;
	//glm::vec3 v = ray.dir;
	//glm::vec3 s3 = ray.start;
	glm::vec4 s(ray.start, 1);
	float ndotv = glm::dot(n, ray.dir);
	//std::cout << ndotv << std::endl;
	//if the abs of ndotv is smaller or equal to FLT_EPSILON
	if (abs(ndotv) <= FP_INFINITE) {
		float ndotsplusd = glm::dot(glm::vec4(x,y,z,w), s);
		return abs(ndotsplusd) <= FLT_EPSILON ? (glm::vec3(FP_INFINITE, FP_INFINITE, FP_INFINITE)) : glm::vec3(NULL, NULL, NULL);
		//line is contained on the plane				//no intersection 

	}
	//else line is pointing through plane
	else {
		//point on plane
		glm::vec4 v(ray.dir, 0);
		float t = -(glm::dot(glm::vec4(x, y, z, w), s) / glm::dot(glm::vec4(x, y, z, w), v));
		//float t = -(plane.Dot(s) / ndotv);
		return (ray.CurrentPosition(t));
	}


	return glm::vec3();
}
Plane::~Plane() {

};