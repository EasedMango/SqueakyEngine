
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

Window::Window(int width_, int height_, const char* title) : window(nullptr)
{
	width = &width_;
	height = &height_;
	ratio = *width/ *height;
	int major, minor;
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwGetVersion(&major,& minor, NULL);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	//glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	//glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	//glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	//glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	printf("Compiled against GLFW %i.%i.%i\n",
		GLFW_VERSION_MAJOR,
		GLFW_VERSION_MINOR,
		GLFW_VERSION_REVISION);
	window = glfwCreateWindow(*width, *height, title, NULL, NULL);

	if (!window)
	{
		// Window or OpenGL context creation failed
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
//	glfwSetWindowUserPointer(window, reinterpret_cast<void*>(this));

}

void Window::OnDestroy()
{
	glfwDestroyWindow(window);
}




