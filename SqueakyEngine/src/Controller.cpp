
#include"Transform.h"
#include"Actor.h"
#include "Controller.h"
#include "Input.h"

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
	Transform* transform = GetParent()->GetComponent<Transform>();
	glm::vec3 dir(0);
	if (Input::GetInstance().OnKeyHold(GLFW_KEY_W))
		dir += glm::vec3(0, 0, 1);
	if (Input::GetInstance().OnKeyHold(GLFW_KEY_S))
		dir += glm::vec3(0, 0, -1);
	if (Input::GetInstance().OnKeyHold(GLFW_KEY_A))
		dir += glm::vec3(-1, 0, 0);
	if (Input::GetInstance().OnKeyHold(GLFW_KEY_D))
		dir += glm::vec3(1, 0, 1);
	static float px = 0, py = 0;
	glm::vec2 pos = Input::GetInstance().GetMousePos();

	float rotx = pos.x - prevMouse.x;
	float roty = pos.y - prevMouse.y;

	//std::cout << "rot: " << rotx << " " << roty << std::endl;
	glm::vec3 rot = glm::vec3(roty * speed, rotx * speed, 0);
	


	//else if (sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
//	setwindowdimensions();
//}

	float offsetx = 0, offsety = 0;

	float sensivity = 0.1f;






	if (Input::GetInstance().OnKeyHold(GLFW_KEY_W))
		dir += glm::vec3(0, 0, 1);
	if (Input::GetInstance().OnKeyHold(GLFW_KEY_S))
		dir += glm::vec3(0, 0, -1);
	if (Input::GetInstance().OnKeyHold(GLFW_KEY_A))
		dir += glm::vec3(-1, 0, 0);
	if (Input::GetInstance().OnKeyHold(GLFW_KEY_D))
		dir += glm::vec3(1, 0, 1);


		if (rot.x != rot.x || rot.x >= 90.0f || rot.x <= -90.0f) return;

		transform->SetTransform(transform->GetPosition() + dir, transform->GetRotationEuler() + rot);
		prevMouse = pos;

	}


	void Controller::Render() const {

	}

	void Controller::RenderGui()
	{
	}

	//void Controller::HandleKeyEvents(GLFWwindow* window, int key, int scancode, int action, int mods)
