#pragma once
struct Ray;
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
struct Plane 
{

	float x, y, z, w;
	Plane(float x_, float y_, float z_, float w_) : x(x_),y(y_),z(z_),w(w_)
	{
		
	}
	Plane(glm::vec4 plane_);
	Plane(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2);
	Plane();

	glm::vec3 const IntersectionPoint(const Ray& ray);
	~Plane();
};


