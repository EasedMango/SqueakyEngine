#include "Sphere.h"


Sphere::Sphere(const glm::vec3& pos_, const float& radius_) : pos(pos_), radius(radius_)
{
}

Sphere::Sphere() : pos(1), radius(1)
{
}

Sphere::~Sphere()
= default;
