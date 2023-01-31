#pragma once


#include <glm/matrix.hpp>

#include "Plane.h"



struct AABB
{
	glm::vec3 min, max;
	glm::mat3 rot;
	/*float rx, ry, rz;*/
	//Plane planes[6];
	glm::vec3 GetCentre() const {return ((rot * min) +(rot * max)); }

	AABB(const float& width, const float& height, const  float& depth);
	AABB();
	~AABB();
	
};

