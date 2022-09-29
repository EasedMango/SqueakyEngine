#include "Physics.h"
#include "PhysicsMath.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>
#include <map>
#include <iomanip>
#include "Components/Gui.h"
#include <cstring>






void const Physics::AddBody(PhysicsBody* body)
{
	bodies.push_back((body));

	++physicsBodies;
}

void const Physics::Update(const float deltaTime)
{
	if (bodies.size() != 0) {
		//for (int x = 0; x < bodies.size() - 1; x++) {

		//	for (int y = x + 1; y < bodies.size(); y++) {

		//		//PhysicsMath::GravityOrbit(*bodies[x], *bodies[y]);

		//	}



		//}

		for (PhysicsBody* p : bodies) {
			

			p->Update(deltaTime);
			PhysicsMath::SimpleVerletMotion(*p, deltaTime);
			PhysicsMath::RigidBodyRotation(*p, deltaTime);
		}

	}



}



void const Physics::OnDestroy()
{
	if (bodies.size() != 0) {
		for (PhysicsBody* p : bodies) {
			p->OnDestroy();
			delete p;
		}
		bodies.clear();
		physicsBodies = 0;
	}
}





void const Physics::RenderGui()
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

