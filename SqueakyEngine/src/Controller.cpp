
#include"Transform.h"
#include"Actor.h"
#include "Controller.h"


Controller::Controller():Component(nullptr) {

}
Controller::~Controller(){

}
bool Controller::OnCreate() {
	return true;
}
void Controller::OnDestroy() {

}
void Controller::Update(const float deltaTime) {

}
void Controller::Render() const {

}

//void Controller::HandleKeyEvents(GLFWwindow* window, int key, int scancode, int action, int mods)
