#pragma once
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
enum class LightStyle {
	DirectionalLight = 1,
	PointLight,
	SkyLight,
	SpotLight
};
class RenderLight
{
public:
	LightStyle lightStyle;
	glm::vec3 position;
	glm::vec4 color;
	float intensity;
	glm::vec3 fallOff;
};
