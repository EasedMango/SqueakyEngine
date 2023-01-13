#pragma once
struct Ray;
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
struct Plane : public glm::vec4
{


	Plane(float x, float y, float z, float w);
	Plane(glm::vec4 plane_);
	Plane(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2);
	Plane();

	glm::vec3 const IntersectionPoint(const Ray& ray);
	~Plane();
};


