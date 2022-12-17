#include"Components/Transform.h"
#include"Components/Actor.h"
#include "ControllerPhysics.h"
#include "Input.h"
#include<glm/ext.hpp>
#include <glm/gtx/compatibility.hpp>
#include <glm/matrix.hpp>
#include <glm/gtx/matrix_operation.hpp>
//#include<glm/gtx/rotate_vector.hpp>
#include <string>
#include "Components/Logger.h"
#include <Vec.h>

#include "ActorManager.h"
using namespace glm;
ControllerPhysics::ControllerPhysics(ActorManager* am) : Component(nullptr),am(am)
{
}

bool ControllerPhysics::OnCreate()
{
	transformCam = am->GetCamera()->GetComponent<Transform>();
	phyBod = GetParentActor()->GetComponent<PhysicsBody>();
	return true;
}

void ControllerPhysics::OnDestroy()
{
}

void ControllerPhysics::Update(const float deltaTime)
{

	vec3 dir(0);
	vec4 rot(0);
	speed = 0.05f;
	if (Input::GetInstance().OnKeyHold(GLFW_KEY_W)) {
		dir -= transformCam->GetForward() * 4.f; //glm::vec3(0, 0, -0.1f);

	}
	if (Input::GetInstance().OnKeyHold(GLFW_KEY_S)) {
		dir += transformCam->GetForward() * 4.f; //glm::vec3(0, 0, 0.1f);

	}
	if (Input::GetInstance().OnKeyHold(GLFW_KEY_A)) {
		dir -= transformCam->GetRight() * 2.f; //glm::vec3(-0.1f, 0, 0);

	}
	if (Input::GetInstance().OnKeyHold(GLFW_KEY_D))
	{
		dir += transformCam->GetRight() * 2.f; //glm::vec3(0.1f, 0, 0);

	}
	if (Input::GetInstance().OnKeyHold(GLFW_KEY_C))
	{
		dir -= transformCam->GetUp();
	}
	if (Input::GetInstance().OnKeyHold(GLFW_KEY_SPACE))
	{
		dir += transformCam->GetUp();
	}
	if (Input::GetInstance().OnKeyHold(GLFW_KEY_Q))
	{
		rot.z += 0.025f;
	}
	if (Input::GetInstance().OnKeyHold(GLFW_KEY_E))
	{
		rot.z -= 0.025f;
	}
	if (Input::GetInstance().OnKeyHold(GLFW_KEY_F))
	{
		//float dotCheck = dot(normalize(phyBod->GetVel()), dir);
		dir = -phyBod->GetVel();

	}
	if (length(dir) >= FLT_EPSILON)
	{
		dir = normalize(dir);
		//printf("normal\n");
	}


	vec2 pos = Input::GetInstance().GetMousePos();




	if (Input::GetInstance().OnClickHold(GLFW_MOUSE_BUTTON_2))
	{
		float rotx = pos.x - prevMouse.x;
		float roty = pos.y - prevMouse.y;
		rot += vec4(roty * speed, rotx * speed, 0, 0);

		float offsetx = 0, offsety = 0;
		float sensivity = 0.1f;

		quat bodRot = phyBod->GetRotation();
		quat xRot = glm::angleAxis(rot.x, vec3(1, 0, 0));
		quat yRot = glm::angleAxis(-rot.y, vec3(0, 1, 0));
		quat zRot = glm::angleAxis(rot.z, vec3(0, 0, 1));


		quat rotation =  bodRot * xRot * yRot * zRot;
		phyBod->SetRotation(slerp(bodRot, rotation,0.5f));
	}






	

	phyBod->AddForce(dir);

	prevMouse = pos;
}


void ControllerPhysics::Render() const
{
}

void ControllerPhysics::RenderGui()
{
}

//void Controller::HandleKeyEvents(GLFWwindow* window, int key, int scancode, int action, int mods)
