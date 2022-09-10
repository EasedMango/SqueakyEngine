#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "Component.h"
#include "Components.h"
#include "Input.h"

class Controller : public Component {
private:
	Actor* GetParent() {
		return (Actor*)parent;
	}
	glm::vec2 prevMouse;
	float speed;
public:
	Controller();
	 ~Controller();
	 bool OnCreate() override;
	 void OnDestroy() override;
	 void Update(const float deltaTime) override;
	 void Render() const override;
	 void KeyEvents(class GLFWwindow* window){
	
	 }
	 void RenderGui() override;

	 void HandleKeyEvents(class GLFWwindow* window, int key, int scancode, int action, int mods) {

		 
	 };
};
