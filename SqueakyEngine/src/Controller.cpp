
#include"Transform.h"
#include"Actor.h"
#include "Controller.h"
#include "Input.h"
#include<glm/ext.hpp>
#include<glm/glm.hpp>
Controller::Controller() :Component(nullptr) {

}
Controller::~Controller() {

}
bool Controller::OnCreate() {
	speed = 0.05f;
	return true;
}
void Controller::OnDestroy() {

}
void Controller::Update(const float deltaTime) {
	Transform* transform = GetParentActor()->GetComponent<Transform>();
	Transform* transformCam = GetParentActor()->GetChildren()[0]->GetComponent<Transform>();
	glm::vec3 dir(0);
	
	if (Input::GetInstance().OnKeyHold(GLFW_KEY_W))
		dir -= transformCam->GetForward()*0.1f;//glm::vec3(0, 0, -0.1f);
	if (Input::GetInstance().OnKeyHold(GLFW_KEY_S))
		dir += transformCam->GetForward() * 0.1f;//glm::vec3(0, 0, 0.1f);
	if (Input::GetInstance().OnKeyHold(GLFW_KEY_A))
		dir -= transformCam->GetRight() * 0.1f;//glm::vec3(-0.1f, 0, 0);
	if (Input::GetInstance().OnKeyHold(GLFW_KEY_D))
		dir += transformCam->GetRight() * 0.1f;//glm::vec3(0.1f, 0, 0);
	if (Input::GetInstance().OnKeyPress(GLFW_KEY_SPACE)) {
		printf("jump");
	}
	glm::vec3 rot(0);
	glm::vec2 pos = Input::GetInstance().GetMousePos();
	if (Input::GetInstance().OnClickHold(GLFW_MOUSE_BUTTON_2)) {
		static float px = 0, py = 0;
		

		float rotx = pos.x - prevMouse.x;
		float roty = pos.y - prevMouse.y;
		rot = glm::vec3(roty * speed, rotx * speed, 0);

		float offsetx = 0, offsety = 0;
		float sensivity = 0.1f;

		if (rot.x != rot.x || rot.x >= 90.0f || rot.x <= -90.0f) return;
		
	}
	transform->SetTransform(transform->GetPosition() + dir, transform->GetRotationEuler() + rot, transform->GetScale()+Input::GetInstance().GetScrollWheel()*0.1f);
	prevMouse = pos;

}


void Controller::Render() const {

}

void Controller::RenderGui()
{
}

//void Controller::HandleKeyEvents(GLFWwindow* window, int key, int scancode, int action, int mods)
