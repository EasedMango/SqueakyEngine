#pragma once
#include <glm/matrix.hpp>
#include "Component.h"
#include "Actor.h"

enum CameraType { Prespective, Orthographic };
class Camera : public Component
{
private:
	CameraType type;
	float fov;
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
	class Transform* camTrn;


public:
	inline static Camera* mainCamera=nullptr;
	Camera(float fov_);




	void UpdateViewMatrix();

	static Camera* GetMainCamera();

	bool OnCreate() override;


	 void OnDestroy() override;


	 void Update(const float deltaTime) override;


	 void Render() const override;


	 void RenderGui() override;

	glm::mat4 GetProjectionMatrix() const { return projectionMatrix; }
	//glm::vec3 Get
	glm::mat4 GetViewMatrix() const;

};

