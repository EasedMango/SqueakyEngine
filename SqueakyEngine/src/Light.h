#pragma once
#include "Component.h"
#include <glm/vec3.hpp>
class Light : public Component
{
private:
	glm::vec3 color;
	float ambientIntensity;
public:
	 bool OnCreate() ;
	 void OnDestroy() ;
	 void Update(const float deltaTime) ;
	 void Render() const ;
	 void RenderGui() ;
};

