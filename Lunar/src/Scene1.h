#pragma once
#include "Scene.h"
#include "Components/Actor.h"

class Scene1 : public Scene
{
private:
    class ActorManager* am;


public:
    explicit Scene1();
    ~Scene1() override;

    bool OnCreate() override;
    void OnDestroy() override;
    void Update(float deltaTime) override;
    void Render() const override;
    void HandleEvents() override;
    void RenderGui() override;
};
