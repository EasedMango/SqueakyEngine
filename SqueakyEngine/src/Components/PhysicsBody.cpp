#include "PhysicsBody.h"
#include <iomanip>
#include <iostream>
#include "Actor.h"
#include <imgui.h>
#include "Gui.h"


PhysicsBody::PhysicsBody(bool isStatic_, float mass_, glm::vec3 vel) :Component(nullptr), isStatic(isStatic_),
                                                                      mass(mass_), acceleration(0), prevAccel(0),
                                                                      rotationVelocity(0), rotationAcceleration(0),
                                                                      length(1), width(1), height(1), radius(1),
                                                                      transform(nullptr)
{

	velocity = vel;

}

void PhysicsBody::Update(const float deltaTime)
{
	//if (!isStatic) {
	glm::vec3 fNet(0);

	for (const glm::vec3& f : forces) {
		fNet += f;
	}

	if (glm::length(fNet) > 1.f) {
		//std::cout << "mag\n";
	}
	//std::cout << glm::length(fNet) << std::endl;
	ApplyForce(fNet);

	forces.clear();
	//}
}

bool PhysicsBody::OnCreate()
{
	transform = dynamic_cast<Actor*>(GetParent())->GetComponent<Transform>();

	return true;
}

void PhysicsBody::OnDestroy()
{
}

void PhysicsBody::Render() const
{
}

void PhysicsBody::RenderGui()
{






	glm::vec3 xyz = GetVel();
	Gui::GuiV3("Velocity: ", xyz);
	SetVel(xyz);

	xyz = GetAccel();
	Gui::GuiV3("Acceleration: ", xyz);
	SetAccel(xyz);

	xyz = GetRotVel();
	Gui::GuiV3("Rot Velocity: ", xyz);
	SetRotVel(xyz);

	xyz = GetRotAccel();
	Gui::GuiV3("Rot Acceleration: ", xyz);
	SetRotAccel(xyz);

	xyz = GetDepthPen();
	Gui::GuiV3("Depth Penatration: ", xyz);



}

Collider* PhysicsBody::GetCollider() const
{
	return dynamic_cast<Actor*>(GetParent())->GetComponent<Collider>();
}

void const PhysicsBody::Print()
{

}
