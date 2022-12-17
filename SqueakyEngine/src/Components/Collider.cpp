#include "Collider.h"
#include "Gui.h"
#include <variant>
#include "Physics/Geometry3D.h"


Collider::Collider() : Component(nullptr)
{
}

Collider::~Collider()
{
}

void Collider::Update(const float deltaTime)
{
}

bool Collider::OnCreate()
{
    return true;
}

void Collider::OnDestroy()
{
}

void Collider::Render() const
{
}

void Collider::RenderGui()
{
    if (std::holds_alternative<Geometry::AABB*>(shape))
    {
        Geometry::AABB* bc = (std::get<0>(shape));
        Gui::GuiV3("Origin", bc->center);
        Gui::GuiV3("Size", bc->radius);
    }
    else if (std::holds_alternative<Geometry::Sphere*>(shape))
    {
        Geometry::Sphere* bc = std::get<1>(shape);
        Gui::GuiV3("Origin", bc->center);
        //Gui::GuiV3("Size", bc->radius);
    }
}

void Collider::OnCollision()
{
}

bool Collider::IsColliding(const Collider* col)
{
    for (const Collider* c : handles)
    {
        if (col == c)
        {
            return true;
        }
    }
    return false;
}
