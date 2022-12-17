#include "Listener.h"
#include <fmod.hpp>
#include "Components/Actor.h"
#include "Audio.h"
#include <cstdio>
#include <fmod.hpp>
#include <fmod_errors.h>
#include <cstdlib>
#include <iostream>
#include <string>

#include "Components/Actor.h"
#include "Components/Component.h"
#include "Components/Transform.h"

Listener::Listener(Audio* system) : ::Component(nullptr), system(system), player(nullptr)
{
}


Listener::~Listener()
{
}

bool Listener::OnCreate()
{
	player = dynamic_cast<Actor*>(GetParent())->GetComponent<Transform>();
	return true;
}

void Listener::OnDestroy()
{
}

void Listener::Update(const float deltaTime)
{

}

void Listener::Render() const
{
}

void Listener::RenderGui()
{
}

glm::vec3 Listener::GetPos() const
{
	return player->GetPosition();
}

glm::vec3 Listener::GetVel() const
{
	return player->GetDelta();
}

glm::vec3 Listener::GetForward() const
{
	return player->GetForward();
}

glm::vec3 Listener::GetUp() const
{
	return player->GetUp();
}




