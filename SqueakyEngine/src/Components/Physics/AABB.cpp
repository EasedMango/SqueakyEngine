#include "AABB.h"
AABB::AABB(const float& width, const float& height, const  float& depth) : min(0, 0, 0), max(width,height,depth) {


	planes[0] = Plane(1, 0, 0, min.x);
	planes[1] = Plane(0, 1, 0, min.y);
	planes[2] = Plane(0, 0, 1, min.z);
	planes[3] = Plane(1, 0, 0, -max.x);
	planes[4] = Plane(0, 1, 0, -max.y);
	planes[5] = Plane(0, 0, 1, -max.z);
}

AABB::AABB(): min(0,0,0), max(1,1,1)
{
	planes[0] = Plane(1, 0, 0, min.x);
	planes[1] = Plane(0, 1, 0, min.y);
	planes[2] = Plane(0, 0, 1, min.z);
	planes[3] = Plane(1, 0, 0, -max.x);
	planes[4] = Plane(0, 1, 0, -max.y);
	planes[5] = Plane(0, 0, 1, -max.z);
}

AABB::~AABB()
= default;
