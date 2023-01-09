#include "Enemy.h"
#include <vector>
#include "Player.h"
#include "Missle.h"
#include "ActorManager.h"
Enemy::Enemy(ActorManager* am): am(am)
{
    health = 20.0f;
    speed = 1;
}

Enemy::~Enemy()
{
}

bool Enemy::OnCreate()
{
    StationTransform = am->GetActor("SpaceStation")->GetComponent<Transform>();
    PlayerTransform = am->GetActor("Player")->GetComponent<Transform>();
    SelfTransform = dynamic_cast<Actor*>(GetParent())->GetComponent<PhysicsBody>();
    return false;
}

void Enemy::Update(const float deltaTime)
{

    for (const Collider* c : dynamic_cast<Actor*>(GetParent())->GetComponent<Collider>()->GetHandles())
    {
        if (dynamic_cast<Actor*>(c->GetParent())->GetComponent<Player>() != nullptr)
        {
            health -= 5.0f;
        }
        if (const Missle* miss =dynamic_cast<Actor*>(c->GetParent())->GetComponent<Missle>(); miss != nullptr)
        {
            am->DestroyActor(dynamic_cast<Actor*>(c->GetParent()));
            health -= miss->GetDamage();
        }
    }
    if (health <= 0) {
        am->DestroyActor(dynamic_cast<Actor*>(GetParent()));

        return;
    }

    float distanceToStation = glm::distance(SelfTransform->GetPos(), StationTransform->GetPosition());
    float distanceToPlayer = glm::distance(SelfTransform->GetPos(), PlayerTransform->GetPosition());

    float stationDamageRange = 25;

    float playerDetectionRange = 75;
    float playerDamageRange = 25;

    // Targets player if player is within detection range and is closer than the space station
    if (distanceToPlayer > playerDamageRange && distanceToPlayer <= playerDetectionRange && distanceToStation > distanceToPlayer) 
    {
        glm::vec3 dir = (glm::normalize(PlayerTransform->GetPosition() - SelfTransform->GetPos()));
        SelfTransform->AddForce(dir * speed);        
        SelfTransform->SetRotation(glm::quatLookAt(dir, glm::vec3(0, 1, 0)));
    }

    else if (distanceToStation > stationDamageRange && distanceToPlayer > playerDamageRange) 
    {
        SelfTransform->AddForce(glm::normalize(StationTransform->GetPosition() - SelfTransform->GetPos()) * speed);
    }

    if (distanceToPlayer <= playerDamageRange || distanceToStation <= stationDamageRange) 
    {
        SelfTransform->SetVel({ 0, 0, 0});
    }

    
}
