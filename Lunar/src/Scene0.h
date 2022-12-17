#pragma once
#include <Scene.h>

class Scene0 : public Scene
{
private:
public:
    explicit Scene0();
    virtual ~Scene0();

    virtual bool OnCreate();
    virtual void OnDestroy();
    virtual void Update(float deltaTime);
    virtual void Render() const;
    virtual void HandleEvents();
    virtual void RenderGui();
};
