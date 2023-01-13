#include "Ray.h"
Ray::Ray(const glm::vec3& start_, const glm::vec3& dir_)
{
	start = start_;
	dir = dir_;

}

Ray::~Ray() = default;;
