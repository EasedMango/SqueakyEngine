#pragma once
#include <Components/Component.h>
#include "Vec.h"
class Missle : public Component
{
private:
	class Actor* target;
	float speed;
	float damage;
	class PhysicsBody* transform;
	glm::vec3 dir{};
public:
	Missle(Component* const parent_, class Actor* target, const float speed, const float damage, const glm::vec3 dir);
	inline float GetDamage()const { return damage; }
	bool OnCreate() override;
	void OnDestroy() override;
	void Update(const float deltaTime) override;
	void Render() const override;
	void RenderGui() override;


};

