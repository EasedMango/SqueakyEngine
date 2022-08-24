#pragma once
#include "Window.h"

class Events
{
private:
	Window *window;
public:
	Events() {};
	Events(Window* window_) { window = window_; };
	~Events() {};
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GLFW_TRUE);

	}
};

