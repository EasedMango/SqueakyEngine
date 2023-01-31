#include "Physics.h"
#include "PhysicsMath.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>
#include <map>
#include <iomanip>
#include "Components/Gui.h"
#include <cstring>
#include "PhysicsMath.h"
#include "ColliderMath.h"
#include "Components/Actor.h"
#include "Components/Physics/AABB.h"
#include "Components/Physics/Sphere.h"
#include "Components/Physics/Ray.h"

bool Physics::Raycast(const glm::vec3& pos, const glm::vec3& dir, Rayhit& rayhit) const
{
	float distance = 1000;

	for (const auto &body : bodies)
	{

		Ray ray(pos, dir);
		//if (const auto  ab = body->GetShape<AABB>(); ab != nullptr)
		//{
		//	if (const glm::vec3 point= ColliderMath::RayAABCollisionPoint(ray, *ab); point.x != FLT_EPSILON)
		//	{
		//		rayhit.actor = dynamic_cast<Actor*>(body->GetParent());
		//		rayhit.point = point;
		//		rayhit.normal = glm::vec3(0, 0, 0);
		//		rayhit.distance = glm::distance(pos, point);
		//		return true;
		//	}
		//		return false;
		//}

		if (const auto  ab = body->GetShape<Sphere>(); ab != nullptr)
		{
			if (const glm::vec3 point = ColliderMath::RaySphereCollisionPoint(ray, *ab); point.x != FLT_EPSILON)
			{
				rayhit.actor = dynamic_cast<Actor*>(body->GetParent());
				rayhit.point = point;
				rayhit.normal = glm::vec3(0, 0, 0);
				rayhit.distance = glm::distance(pos, point);
				return true;
			}
				return false;
		}
	}
	if (rayhit.actor != nullptr)
	{
		return true;
	}
	return false;



}
void Physics::AddBody(PhysicsBody* body)
{
	bodies.push_back((body));

	++physicsBodies;
}

void Physics::Update(const float deltaTime) const
{
	if (!bodies.empty())
	{


		for (int x = 0; x < bodies.size() - 1; x++)
		{
			for (int y = x + 1; y < bodies.size(); y++)
			{
				if (PhysicsMath::CheckColliders(*bodies[x], *bodies[y]))
				{
					//bodies[x]->GetCollider()->AddHandle(bodies[y]->GetCollider());
					//bodies[y]->GetCollider()->AddHandle(bodies[x]->GetCollider());
					//PhysicsMath::CollisionResponse(bodies[x], bodies[y]);
				}
			}
		}
		for (PhysicsBody* p : bodies)
		{
			p->GetCollider()->ClearHandles();
			p->Update(deltaTime);
			PhysicsMath::SimpleVerletMotion(*p, deltaTime);
			PhysicsMath::RigidBodyRotation(*p, deltaTime);
		}
	}
}

void Physics::RemoveBody(PhysicsBody* pb)
{
	for (const PhysicsBody* a : bodies)
	{
		if (a == pb)
		{
			for (auto i = bodies.begin(); i != bodies.end(); ++i)
			{
				if (*i == a)
				{
					bodies.erase(i);
					break;
				}
			}
			break;
		}
	}
}


void Physics::OnDestroy()
{
	if (!bodies.empty())
	{
		for (PhysicsBody* p : bodies)
		{
			p->OnDestroy();
			delete p;
		}
		bodies.clear();
		physicsBodies = 0;
	}
}


void Physics::RenderGui()
{
	//ImGui::Begin("Main Menu");                          // Create a window called "Hello, world!" and append into it.
	////ImGui::


	//ImGui::Text("Physics Engine:");             // Display some text (you can use a format strings too
	//static int current = 0;

	//const int size = sizeof(bodies.data()) / sizeof(bodies.data()[0]);
	////std::cout <<(size)<<std::endl;
	//const char* a[size];
	//for (size_t i = 0; i < size; i++)
	//{
	//	const char* name = bodies[i]->GetName();
	//	a[i] = name;
	//}
	//ImGui::ListBox("Physics Bodies", &current, a, IM_ARRAYSIZE(a), 4);


	////if (ImGui::TreeNode("Transform")) {

	//	
	//	glm::vec3 xyz = bodies[current]->GetPos();
	//	Gui::Gui::GuiV3("Position: ", xyz);
	//	bodies[current]->SetPos(xyz);

	//	xyz = bodies[current]->GetRotation();
	//	Gui::GuiV3("Rotation: ", xyz);
	//	bodies[current]->SetRotation(xyz);

	//	xyz = bodies[current]->GetScale();
	//	Gui::GuiV3("Scale: ", xyz);
	//	bodies[current]->SetScale(xyz);
	////	ImGui::TreePop();
	////}
	//if (ImGui::TreeNode("Movement")) {

	//	glm::vec3 xyz = bodies[current]->GetVel();
	//	Gui::GuiV3("Velocity: ", xyz);
	//	bodies[current]->SetVel(xyz);

	//	 xyz = bodies[current]->GetAccel();
	//	Gui::GuiV3("Acceleration: ", xyz);
	//	bodies[current]->SetAccel(xyz);

	//	 xyz = bodies[current]->GetRotVel();
	//	Gui::GuiV3("Rot Velocity: ", xyz);
	//	bodies[current]->SetRotVel(xyz);

	//	 xyz = bodies[current]->GetRotAccel();
	//	Gui::GuiV3("Rot Acceleration: ", xyz);
	//	bodies[current]->SetRotAccel(xyz);


	//	ImGui::TreePop();
	//}
	//ImGui::End();
}
