#pragma once


#include <glm/mat3x3.hpp>
#include <glm/vec3.hpp>

struct OBB
{
	glm::vec3 center;
	glm::vec3 extents;
	glm::mat3 rotation;
	OBB(const float& width, const float& height, const  float& depth);
	OBB()=default;
	~OBB()=default;
};

