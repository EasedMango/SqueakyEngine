#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "Component.h"
#include "Components.h"

class Controller : public Component {
private:
	Actor* GetParent() {
		return (Actor*)parent;
	}

public:
	Controller();
	 ~Controller();
	 bool OnCreate() override;
	 void OnDestroy() override;
	 void Update(const float deltaTime) override;
	 void Render() const override;
	 void KeyEvents(class GLFWwindow* window){
		// int state = glfwGetKey(window, GLFW_KEY_E);
		 if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		 {
			 GetParent()->GetComponent<Transform>()->SetTransform(glm::vec3(0, 0, 0), glm::quat(glm::vec3(0, 0, glfwGetTime())));
		 }
	 }

	 void HandleKeyEvents(class GLFWwindow* window, int key, int scancode, int action, int mods) {
		 //int state = glfwGetKey(window, GLFW_KEY_E);
		 //if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS&& glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		 //{
			// GetParent()->GetComponent<Transform>()->SetTransform(glm::vec3(0, 0, 0), glm::quat(glm::vec3(0, 0, glfwGetTime())));
		 //}
		 //if (key == GLFW_KEY_W && action == GLFW_PRESS) {
			// //static_cast<Actor>(parent).GetComponent<Transform>()->SetTransform(glm::vec3(0, 0, 0), glm::quat(glm::vec3(0, 0, glfwGetTime())));
			//GetParent()->GetComponent<Transform>()->SetTransform(glm::vec3(0,1,0), glm::quat(glm::vec3(0, 0, glfwGetTime())));
		 //}
		 //if (key == GLFW_KEY_S && action == GLFW_PRESS) {
			// //static_cast<Actor>(parent).GetComponent<Transform>()->SetTransform(glm::vec3(0, 0, 0), glm::quat(glm::vec3(0, 0, glfwGetTime())));
			// GetParent()->GetComponent<Transform>()->SetTransform(glm::vec3(0,-1,0), glm::quat(glm::vec3(0, 0, glfwGetTime())));
		 //}
		 //if (key == GLFW_KEY_TAB && action == GLFW_PRESS)
			// glfwSetWindowShouldClose(window, GLFW_TRUE);
	 };
};
