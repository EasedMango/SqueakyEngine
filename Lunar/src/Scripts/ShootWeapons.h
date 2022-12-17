#pragma once
#include <Components/Component.h>
class ActorManager;
class Actor;
class ShootWeapons : public Component
{

private:
	ActorManager* am;
	Actor* laser;

public:
	explicit ShootWeapons(ActorManager* const am);

	bool OnCreate() override;
	void OnDestroy() override;
	void Update(const float deltaTime) override;
	void Render() const override;
	void RenderGui() override;
};

