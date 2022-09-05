#pragma once
#include <glm/matrix.hpp>
#include "Component.h"
class Camera : public Component
{
private:
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
public:
	 bool OnCreate() override;
	 void OnDestroy() override;
	 void Update(const float deltaTime) override;
	 void Render() const override;
	Camera(float fov, float ratio);
	glm::mat4 GetProjectionMatrix() { return projectionMatrix; }
	glm::mat4 GetViewMatrix() { return viewMatrix; }
};

