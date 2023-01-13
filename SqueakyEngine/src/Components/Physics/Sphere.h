#pragma once
#include <glm/vec3.hpp>

struct Sphere
{

	glm::vec3 pos;
	float radius;
	Sphere(const glm::vec3& pos_, const float& radius_);
	Sphere();
	~Sphere();
};
