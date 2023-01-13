#pragma once
#include <glm/vec3.hpp>

struct Ray
{
	glm::vec3 start;
	glm::vec3 dir;

	Ray(const glm::vec3& start_, const glm::vec3& dir_);

	~Ray();

	glm::vec3  CurrentPosition(const float& t) const {
		return start + dir * t;
	};
};

