#include"Components/Transform.h"
#include"Components/Actor.h"
#include "Controller.h"
#include "Input.h"
#include<glm/ext.hpp>
#include<glm/glm.hpp>
using namespace glm;
Controller::Controller() : Component(nullptr)
{
}

Controller::~Controller()
{
}

bool Controller::OnCreate()
{
	phyBod = GetParentActor()->GetComponent<PhysicsBody>();
	transform = GetParentActor()->GetComponent<Transform>();
    speed = 0.05f;
    return true;
}

void Controller::OnDestroy()
{
}

void Controller::Update(const float deltaTime)
{
	

    glm::vec3 dir(0);
	glm::vec4 rot(0);
	if (Input::GetInstance().OnKeyHold(GLFW_KEY_W)) {
		dir += vec3(0, 1, 0) *2.f; //glm::vec3(0, 0, -0.1f);

	}
	if (Input::GetInstance().OnKeyHold(GLFW_KEY_S)) {
		dir -= vec3(0, 1, 0)* 2.f; //glm::vec3(0, 0, 0.1f);

	}
	if (Input::GetInstance().OnKeyHold(GLFW_KEY_A)) {
		dir -= vec3(1, 0, 0) * 2.f; //glm::vec3(-0.1f, 0, 0);

	}
	if (Input::GetInstance().OnKeyHold(GLFW_KEY_D))
	{
		dir += vec3(1, 0, 0) * 2.f; //glm::vec3(0.1f, 0, 0);

	}
	if (Input::GetInstance().OnKeyHold(GLFW_KEY_C))
	{
		dir -= transform->GetForward();
	}
	if (Input::GetInstance().OnKeyHold(GLFW_KEY_SPACE))
	{
		dir += transform->GetForward();
	}
	if (Input::GetInstance().OnKeyHold(GLFW_KEY_Q))
	{
		rot.z += 0.025f;
	}
	if (Input::GetInstance().OnKeyHold(GLFW_KEY_E))
	{
		rot.z -= 0.025f;
	}

	vec2 pos = Input::GetInstance().GetMousePos();




	if (Input::GetInstance().OnClickHold(GLFW_MOUSE_BUTTON_2))
	{
		float rotx = pos.x - prevMouse.x;
		float roty = pos.y - prevMouse.y;
		rot += vec4(roty * speed, rotx * speed, 0, 0);

		float offsetx = 0, offsety = 0;
		float sensivity = 0.1f;

	}
	quat bodRot = phyBod->GetRotation();
	quat xRot = glm::angleAxis(rot.x, vec3(1, 0, 0));
	quat yRot = glm::angleAxis(-rot.y, vec3(0, 1, 0));
	quat zRot = glm::angleAxis(rot.z, vec3(0, 0, 1));


	quat rotation = bodRot * xRot * yRot * zRot;
	phyBod->SetRotation(slerp(bodRot, rotation, 0.5f));








	phyBod->AddForce(dir);

	prevMouse = pos;
}


void Controller::Render() const
{
}

void Controller::RenderGui()
{
}

//void Controller::HandleKeyEvents(GLFWwindow* window, int key, int scancode, int action, int mods)
