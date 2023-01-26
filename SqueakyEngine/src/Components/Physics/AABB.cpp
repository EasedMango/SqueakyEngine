#include "AABB.h"
AABB::AABB(const float& width, const float& height, const  float& depth) : min(-width / 2,- height / 2, -depth / 2), max(width/2,height/2,depth/2) {


}

AABB::AABB(): min(-0.5f, -0.5f, -0.5f), max(0.5f,0.5f,0.5f)
{

}

AABB::~AABB()
= default;
