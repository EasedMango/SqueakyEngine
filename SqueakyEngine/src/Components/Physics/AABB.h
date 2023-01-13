#pragma once
#include "Plane.h"



struct AABB
{
	glm::vec3 min, max;
	/*float rx, ry, rz;*/
	Plane planes[6];


	AABB(const float& width, const float& height, const  float& depth);
	AABB();
	~AABB();
	
};

