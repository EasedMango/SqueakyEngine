#include "Collider.h"
#include "Gui.h"
#include <variant>

#include "Physics/OBB.h"
#include "Physics/Geometry3D.h"
#include "Physics/Sphere.h"


Collider::Collider() : Component(nullptr)
{
}

Collider::~Collider()
= default;

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
    if (std::holds_alternative<OBB*>(shape))
    {
        OBB* bc = (std::get<0>(shape));
        Gui::GuiV3("Origin", bc->center);
        Gui::GuiV3("Size", bc->extents);
    }
    else if (std::holds_alternative<Sphere*>(shape))
    {
        Sphere* bc = std::get<1>(shape);
        Gui::GuiV3("Origin", bc->pos);
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
