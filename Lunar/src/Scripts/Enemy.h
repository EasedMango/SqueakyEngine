#pragma once
#include "Entity.h"

class Enemy : public Entity
{
private:
    class Transform* StationTransform;
    class Transform* PlayerTransform;
    class PhysicsBody* SelfTransform;

    float speed;

    class ActorManager* am;

public:
    Enemy(class ActorManager* am);
    ~Enemy() override;

    bool OnCreate() override;

    

    void Update(float deltaTime) override;
};
