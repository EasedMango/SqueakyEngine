#include "Entity.h"
#include "imgui.h"
#include "Input.h"
#include <GLFW/glfw3.h>

Entity::Entity() : Component(nullptr)
{
}

Entity::~Entity()
{
}

bool Entity::OnCreate()
{
    return false;
}

void Entity::OnDestroy()
{
}

void Entity::Update(const float deltaTime)
{
    std::cout << (health) << std::endl;
    if (Input::GetInstance().OnKeyPress(GLFW_KEY_F))
    {
        TakeDamage(10);
    }
}

void Entity::Render() const
{
}

void Entity::RenderGui()
{
    ImGui::DragFloat("Health", &health);
}
