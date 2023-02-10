#pragma once
#include <glm/matrix.hpp>
#include "Component.h"
#include "Actor.h"
#include "RenderCamera.h"


class Camera : public Component, public RenderCamera
{
private:
	class Transform* camTrn;


public:
	inline static Camera* mainCamera = nullptr;
	Camera(float fov_);






	static Camera* GetMainCamera();

	bool OnCreate() override;


	void OnDestroy() override;


	void Update(const float deltaTime) override;


	void Render() const override;



	void RenderGui() override;


	void UpdateViewMatrix() override;
};

