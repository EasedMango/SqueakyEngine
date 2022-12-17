#pragma once
#include <glm/matrix.hpp>
#include "Component.h"
#include "Actor.h"

class Camera : public Component
{
private:
	float fov;
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
	class Transform* camTrn;


public:
	Camera(float fov_);
	void UpdateViewMatrix();
	void UpdateViewMatrix(glm::vec3 pos);
	 bool OnCreate() override;
	 void OnDestroy() override;
	 void Update(const float deltaTime) override;
	 void Render() const override;
	 void SendUniforms( class Shader* shader);
	 void RenderGui() override;

	glm::mat4 GetProjectionMatrix() const { return projectionMatrix; }
	//glm::vec3 Get
	glm::mat4 GetViewMatrix() const;

};

