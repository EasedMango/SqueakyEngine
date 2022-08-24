
#include "Window.h"
#include <cmath>
#include <gl/GL.h>

void DrawCircle() {
	const float angle = 3.1415926 * 2.0f;
	float xPos = 0; float yPos = 0; float radius = 1.0f;
	float prevX = xPos;
	float prevY = yPos = radius;


}
Window::Window()
{
}

Window::Window(int width, int height, const char* title) : window(nullptr)
{
	int major, minor;
	glfwGetVersion(&major,& minor, NULL);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!window)
	{
		// Window or OpenGL context creation failed

	}
	
	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, reinterpret_cast<void*>(this));

}




