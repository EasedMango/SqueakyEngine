#pragma once
#include "Components/Component.h"
#include <glm/vec3.hpp>
class Audio;

class Listener :
    public Component
{
private:
	Audio* system;

	class Transform* player;
public:
	Listener(Audio* system);
	~Listener() override;
	bool OnCreate() override;
	void OnDestroy() override;
	void Update(const float deltaTime) override;
	void Render() const override;
	void RenderGui() override;
	glm::vec3 GetPos() const;
	glm::vec3 GetVel() const;
	glm::vec3 GetForward() const;
	glm::vec3 GetUp() const;
};

