#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "Component.h"
#include "Components.h"
#include "Input.h"

class ControllerPhysics : public Component {
private:
	Actor* GetParentActor() {
		return static_cast<Actor*>( parent);	}
	glm::vec2 prevMouse;
	float speed;
public:
	ControllerPhysics();
	 ~ControllerPhysics();
	 bool OnCreate() override;
	 void OnDestroy() override;
	 void Update(const float deltaTime) override;
	 void Render() const override;
	 void KeyEvents(struct GLFWwindow* window){
	
	 }
	 void RenderGui() override;

	 void HandleKeyEvents(struct GLFWwindow* window, int key, int scancode, int action, int mods) {

		 
	 };
};
