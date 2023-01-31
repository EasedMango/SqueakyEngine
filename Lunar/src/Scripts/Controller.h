#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "Components.h"
#include "Input.h"

class Controller : public Component
{
private:
    Actor* GetParentActor()
    {
        return dynamic_cast<Actor*>(parent);
    }

    glm::vec2 prevMouse;
    PhysicsBody* phyBod{};
    Transform* transform{};
    float speed;
public:
    Controller();
    ~Controller() override;
    bool OnCreate() override;
    void OnDestroy() override;
    void Update(float deltaTime) override;
    void Render() const override;

    void KeyEvents(struct GLFWwindow* window)
    {
    }

    void RenderGui() override;

    void HandleKeyEvents(struct GLFWwindow* window, int key, int scancode, int action, int mods)
    {
    };
};
