#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
    Player();
    ~Player() override;
    void Update(float deltaTime) override;
};
