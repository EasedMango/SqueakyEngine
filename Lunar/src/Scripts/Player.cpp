#include "Player.h"
#include "Enemy.h"

Player::Player()
{
    health = 100.0f;
}

Player::~Player()
{
}

void Player::Update(const float deltaTime)
{
    for (const Collider* c : dynamic_cast<Actor*>(GetParent())->GetComponent<Collider>()->GetHandles())
    {
        if (dynamic_cast<Actor*>(c->GetParent())->GetComponent<Enemy>() != nullptr)
        {
            health -= 5.0f;
        }
    }
}
