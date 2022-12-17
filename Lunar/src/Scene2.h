#pragma once
#include "Scene.h"
#include "Components/Actor.h"
#include "SceneManager.h"

class Scene2 : public Scene
{
private:
    class ActorManager* am;

    class Audio* audio;
public:
    explicit Scene2();

    ~Scene2() override;

    bool OnCreate() override;
    void OnDestroy() override;
    void Update(float deltaTime) override;
    void Render() const override;
    void HandleEvents() override;
    void RenderGui() override;
};
