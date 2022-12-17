#pragma once
#include "Component.h"
#include "Physics/Geometry3D.h"
class SphereCollider : public Component, public Geometry::Sphere
{

public: 
     void OnCollisionEnter();
     void OnCollisionStay();
     void OnCollisionExit();
};

