#pragma once

#include "Components/Component.h"

class CameraController :
    public Component
{
private:
	class Transform* transform;
	class Camera* camera;

public:
	explicit CameraController();

	~CameraController() override;
	bool OnCreate() override;
	void OnDestroy() override;
	void Update(const float deltaTime) override;
	void Render() const override;
	void RenderGui() override;
};

