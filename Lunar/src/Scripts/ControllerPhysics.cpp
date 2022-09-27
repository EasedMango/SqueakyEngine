
#include"Transform.h"
#include"Actor.h"
#include "ControllerPhysics.h"
#include "Input.h"
#include<glm/ext.hpp>
#include<glm/glm.hpp>
#include <string>
#include "Logger.h"
ControllerPhysics::ControllerPhysics() :Component(nullptr) {

}
ControllerPhysics::~ControllerPhysics() {

}
bool ControllerPhysics::OnCreate() {

	return true;
}
void ControllerPhysics::OnDestroy() {

}
void ControllerPhysics::Update(const float deltaTime) {
	//Transform* transform = GetParentActor()->GetComponent<Transform>();
	Transform* transformCam = GetParentActor()->GetChildren()[0]->GetComponent<Transform>();
	PhysicsBody* phyBod = GetParentActor()->GetComponent<PhysicsBody>();
	glm::vec3 dir(0);
	speed = 0.05f;
	if (Input::GetInstance().OnKeyHold(GLFW_KEY_W))
		dir -= transformCam->GetForward() * 4.f;//glm::vec3(0, 0, -0.1f);
	if (Input::GetInstance().OnKeyHold(GLFW_KEY_S))
		dir += transformCam->GetForward() * 4.f;//glm::vec3(0, 0, 0.1f);
	if (Input::GetInstance().OnKeyHold(GLFW_KEY_A))
		dir -= transformCam->GetRight() * 4.f;//glm::vec3(-0.1f, 0, 0);
	if (Input::GetInstance().OnKeyHold(GLFW_KEY_D)) {
		dir += transformCam->GetRight() * 4.f;//glm::vec3(0.1f, 0, 0);
	}

	if (glm::length(dir) != 0) { 
		dir = glm::normalize(dir); 
		printf("normal\n");
	}
	if (Input::GetInstance().OnKeyPress(GLFW_KEY_SPACE)) {
		printf("jump");
	}
	glm::vec3 rot(0);
	glm::vec2 pos = Input::GetInstance().GetMousePos();
	std::cout << glm::length(dir) << std::endl;
	if (Input::GetInstance().OnClickHold(GLFW_MOUSE_BUTTON_2)) {



		float rotx = pos.x - prevMouse.x;
		float roty = pos.y - prevMouse.y;
		rot = glm::vec3(roty * speed, rotx * speed, 0);

		float offsetx = 0, offsety = 0;
		float sensivity = 0.1f;

		if (rot.x != rot.x || rot.x >= 90.0f || rot.x <= -90.0f) return;

	}
	//std::string mag = std::string("curn ") +std::to_string(pos.x) + std::to_string(pos.y);
	//std::string mag1 = std::string("prev ") +std::to_string(prevMouse.x) + std::to_string(prevMouse.y);
	//std::string mag2 = std::string("diff ") + std::to_string(prevMouse.x-pos.x) + std::to_string(prevMouse.y-pos.y);
	//Logger::Info(mag);
	//Logger::Info(mag1);
	//Logger::Info(mag2);
	//glm::vec3 vel = phyBod->GetVel();
		//if (glm::length(vel) <= 2)
	phyBod->AddForce(dir);




	phyBod->SetRotation(phyBod->GetRotation() + rot);
	phyBod->SetScale(phyBod->GetScale() + Input::GetInstance().GetScrollWheel() * 0.1f);
	//transform->SetTransform(transform->GetPosition() + dir, transform->GetRotationEuler() + rot, transform->GetScale()+Input::GetInstance().GetScrollWheel()*0.1f);
	prevMouse = pos;

}


void ControllerPhysics::Render() const {

}

void ControllerPhysics::RenderGui()
{
}

//void Controller::HandleKeyEvents(GLFWwindow* window, int key, int scancode, int action, int mods)
