#include "Physics.h"
#include "PhysicsMath.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>
#include <map>
#include <iomanip>
#include "Components/Gui.h"
#include <cstring>
#include "PhysicsMath.h"
#include "Components/Actor.h"


bool Physics::Raycast(const glm::vec3& pos, const glm::vec3& dir, Rayhit& rayhit) const
{
	float distance = 1000;

	//for (const auto bo : bodies)
	//{


	//	auto dir2 = glm::vec3(-dir.x, -dir.y, dir.z);
	//	if (const auto  bc = bo->GetShape<Geometry::AABB>(); bc != nullptr)
	//	{

	//		bc->center = bo->GetPos();
	//		float ma = 0;

	//		if (glm::vec3 mt; Geometry::IntersectRayAABB(pos, dir2, *bc, ma, mt) && distance > ma)
	//		{
	//			distance = ma;
	//			rayhit.actor = dynamic_cast<Actor*>(bo->GetParent());
	//			rayhit.distance = ma;
	//			rayhit.point = (mt);

	//		}

	//	}
	//	if (const auto  bc = bo->GetShape<Geometry::Sphere>(); bc != nullptr)
	//	{
	//		bc->center = bo->GetPos();
	//		float ma = 0;
	//		glm::vec3 mt = { 0,0,0 };

	//		const Geometry::RayResults rayResults = Geometry::RaySphereCollisionPoint(Geometry::Ray(pos, dir2), *bc);

	//		std::cout << "Casting against: " << dynamic_cast<Actor*>(bo->GetParent())->GetName() << std::endl;


	//	

	//		glm::vec3 trigDir = glm::normalize(bo->GetPos() - pos);

	//		const float dot = glm::dot(trigDir, dir2);

	//		const bool isLooking = dot >= 0.4f;




	//		std::cout << "Dot: " << dot << " Threshold: " << 0.4f << std::endl;
	//		std::cout << "Is looking? " << isLooking << std::endl;
	//		std::cout << "Distance:" << rayResults.distance << "\n" << std::endl;



	//		if (rayResults.distance < distance && rayResults.distance > FLT_EPSILON)
	//		{

	//			distance = ma;
	//			rayhit.actor = dynamic_cast<Actor*>(bo->GetParent());
	//			rayhit.distance = rayResults.distance;
	//			rayhit.point = (rayResults.point);

	//		}


	//	}

	//}
	//if (rayhit.actor != nullptr)
	//{
	//	return true;
	//}
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
		for (PhysicsBody* p : bodies)
		{
			p->GetCollider()->ClearHandles();
			p->Update(deltaTime);
			PhysicsMath::SimpleVerletMotion(*p, deltaTime);
			PhysicsMath::RigidBodyRotation(*p, deltaTime);
		}

		for (int x = 0; x < bodies.size() - 1; x++)
		{
			for (int y = x + 1; y < bodies.size(); y++)
			{
				if (PhysicsMath::CheckColliders(*bodies[x], *bodies[y]))
				{
					bodies[x]->GetCollider()->AddHandle(bodies[y]->GetCollider());
					bodies[y]->GetCollider()->AddHandle(bodies[x]->GetCollider());
					PhysicsMath::CollisionResponse(bodies[x], bodies[y]);
				}
			}
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
