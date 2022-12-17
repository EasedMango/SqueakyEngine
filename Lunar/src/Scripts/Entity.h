#pragma once
#include "Components.h"


class Entity : public Component
{
protected:
    float health;

public:
    Entity();
    ~Entity() override;
    bool OnCreate() override;
    void OnDestroy() override;
    void Update(float deltaTime) override;
    void Render() const override;
    void RenderGui() override;
    void TakeDamage(float damage) { health -= damage; }
};
