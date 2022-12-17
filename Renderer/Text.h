#pragma once
#include <string>
#include <glm/vec3.hpp>

class Text
{
public:
	std::string text;
	glm::vec3 position;
	float fontSize;

	Text(const std::string& text, const glm::vec3& pos, const float fontSize);
};

