#pragma once
#include "Scene.h"
#include "Components/Actor.h"

class Scene3 : public Scene
{
private:
    class ActorManager* am;


public:
    explicit Scene3();
    ~Scene3() override;

    bool OnCreate() override;
    void OnDestroy() override;
    void Update(float deltaTime) override;
    void Render() const override;
    void HandleEvents() override;
    void RenderGui() override;
};
