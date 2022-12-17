#pragma once
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/vector_relational.hpp"
#include <iostream>

inline std::ostream& operator << (std::ostream& out, const glm::vec3& c)
{
    out << c.x << " " << c.y << " " << c.z;
    return out;
}