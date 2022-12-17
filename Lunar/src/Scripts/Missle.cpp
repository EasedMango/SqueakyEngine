#include "Missle.h"
#include <Components/Actor.h>
#include <Components/PhysicsBody.h>
Missle::Missle(Component* const parent_, class Actor* target, const float speed, const float damage, const glm::vec3 dir) : Component(parent_),
	target(target),
	speed(speed),
	damage(damage), transform(nullptr)
{
	this->dir = dir;
}

bool Missle::OnCreate()
{
	transform = dynamic_cast<Actor*>(GetParent())->GetComponent<PhysicsBody>();
	return true;
}

void Missle::OnDestroy()
{
}

void Missle::Update(const float deltaTime)
{
	if(target!= nullptr)
	transform->AddForce(glm::normalize(target->GetComponent<PhysicsBody>()->GetPos() - transform->GetPos()) * speed);
	else
		transform->AddForce(glm::normalize(dir) * speed);
	

}

void Missle::Render() const
{
}

void Missle::RenderGui()
{
}
