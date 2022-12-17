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
    speed = 0.05f;
    return true;
}

void Controller::OnDestroy()
{
}

void Controller::Update(const float deltaTime)
{
	auto transform = GetParentActor()->GetComponent<Transform>();

    glm::vec3 dir(0);
	glm::vec3 rot(0);
	if (Input::GetInstance().OnKeyHold(GLFW_KEY_W)) {
		dir += transform->GetForward() * 0.2f; //glm::vec3(0, 0, -0.1f);

	}
	if (Input::GetInstance().OnKeyHold(GLFW_KEY_S)) {
		dir -= transform->GetForward() * 0.2f; //glm::vec3(0, 0, 0.1f);

	}
	if (Input::GetInstance().OnKeyHold(GLFW_KEY_A)) {
		dir -= transform->GetRight() * 0.2f; //glm::vec3(-0.1f, 0, 0);

	}
	if (Input::GetInstance().OnKeyHold(GLFW_KEY_D))
	{
		dir += transform->GetRight() * 0.2f; //glm::vec3(0.1f, 0, 0);

	}
	if (Input::GetInstance().OnKeyHold(GLFW_KEY_C))
	{
		dir -= transform->GetUp();
	}
	if (Input::GetInstance().OnKeyHold(GLFW_KEY_SPACE))
	{
		dir += transform->GetUp();
	}
	if (Input::GetInstance().OnKeyHold(GLFW_KEY_Q))
	{
		rot.z += 0.025f;
	}
	if (Input::GetInstance().OnKeyHold(GLFW_KEY_E))
	{
		rot.z -= 0.025f;
	}

    glm::vec2 pos = Input::GetInstance().GetMousePos();
    if (Input::GetInstance().OnClickHold(GLFW_MOUSE_BUTTON_2))
    {
        static float px = 0, py = 0;


        float rotx = pos.x - prevMouse.x;
        float roty = pos.y - prevMouse.y;
        rot += glm::vec3(roty * speed, rotx * speed, 0);

        float offsetx = 0, offsety = 0;
        float sensivity = 0.1f;

        if (rot.x != rot.x || rot.x >= 90.0f || rot.x <= -90.0f) return;
    }
	quat bodRot = transform->GetRotation();
	quat yRot = glm::angleAxis(rot.x, vec3(1, 0, 0));
	quat xRot = glm::angleAxis(rot.z, vec3(0, 1, 0));
	quat zRot = glm::angleAxis(rot.y, vec3(0, 0, 1));
	quat rotation = bodRot * xRot * yRot * zRot;

	//
	//std::cout << "Dot: " << dotCheck << std::endl;
	//std::cout << "XRotation: " << degrees(bodRot.x) << "YRotation: " << degrees(bodRot.y) << "ZRotation: " << degrees(bodRot.z) << std::endl;
	transform->SetRotation(rotation);
	//if (degrees(abs(bodRot.z)) >= 180) {
		//if (dotCheck <= 0.4f)
			//if (length(phyBod->GetVel()) <= 1.f)
	transform->SetPosition( transform->GetPosition()+(dir));
    prevMouse = pos;
}


void Controller::Render() const
{
}

void Controller::RenderGui()
{
}

//void Controller::HandleKeyEvents(GLFWwindow* window, int key, int scancode, int action, int mods)
