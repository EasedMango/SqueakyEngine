#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "Components/Component.h"
#include "Components.h"
#include "Input.h"

class ControllerPhysics final : public Component
{
private:
	Actor* GetParentActor()
	{
		return dynamic_cast<Actor*>(parent);
	}

	glm::vec2 prevMouse{};
	float speed{};
	Transform* transform{};
	Transform* transformCam{};
	PhysicsBody* phyBod{};
	class ActorManager* am;
public:
	ControllerPhysics(ActorManager* am);
	~ControllerPhysics() override = default;
	bool OnCreate() override;
	void OnDestroy() override;
	void Update(float deltaTime) override;
	void Render() const override;



	void RenderGui() override;


};
