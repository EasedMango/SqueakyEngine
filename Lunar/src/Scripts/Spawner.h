#pragma once
#include "Components/Component.h"
class ActorManager;
class Spawner : public Component
{
private:
	ActorManager* am;

public:
	float timer;
	explicit Spawner(ActorManager* am);
	bool OnCreate() override;
	void OnDestroy() override;
	void Update(const float deltaTime) override;
	void Render() const override;
	void RenderGui() override;
};

