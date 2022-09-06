#pragma once
#include <glm/matrix.hpp>
#include "Component.h"
class Camera : public Component
{
private:
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
public:
	Camera(float fov, float ratio);
	 bool OnCreate() override;
	 void OnDestroy() override;
	 void Update(const float deltaTime) override;
	 void Render() const override;
	
	glm::mat4 GetProjectionMatrix() { return projectionMatrix; }
	glm::mat4 GetViewMatrix() { return viewMatrix; }
};
