#pragma once
#include "Component.h"
#include <queue>
class Collider :
    public Component
{
private:
    bool isColliding;
    std::queue<Collider*> collisionHandles;

public:
    explicit Collider(): isColliding(false),collisionHandles(), Component(nullptr) {}
    virtual ~Collider()=default;
    virtual void OnCollisionEnter()=0;
    virtual void OnCollisionStay()=0;
    virtual void OnCollisionExit()=0;


};

