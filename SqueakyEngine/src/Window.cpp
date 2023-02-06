
#include "Window.h"
#include <cmath>


#include "Input.h"
#include "SceneManager.h"

void DrawCircle() {
	const float angle = 3.1415926 * 2.0f;
	float xPos = 0; float yPos = 0; float radius = 1.0f;
	float prevX = xPos;
	float prevY = yPos = radius;


}
Window::Window()
= default;

Window::Window(const int width_, const int height_, const char* title) : window(nullptr)
{
	Logger::Info("Constructing Window");
	width = width_;
	height = height_;

	int major, minor;
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwGetVersion(&major, &minor, nullptr);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	//glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	//glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	//glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	//glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	const std::string log = ("Compiled against GLFW ") + std::to_string(GLFW_VERSION_MAJOR) + "." + std::to_string(GLFW_VERSION_MINOR) + "." + std::to_string(GLFW_VERSION_REVISION);
	Logger::Info(log);


	//printf("Compiled against GLFW %i.%i.%i\n",
	//	GLFW_VERSION_MAJOR,
	//	GLFW_VERSION_MINOR,
	//	GLFW_VERSION_REVISION);
	window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	Logger::Info("Created Window, " + std::string(title) + " with Width: " + std::to_string(width) + " Height: " + std::to_string(height));
	if (!window)
	{
		// Window or OpenGL context creation failed
		Logger::FatalError("Window or OpenGL context creation failed");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	Logger::Info("Setting Window context");
	glfwMakeContextCurrent(window);
	//	glfwSetWindowUserPointer(window, reinterpret_cast<void*>(this));

}

void Window::OnDestroy() const
{
	glfwDestroyWindow(window);

}

void Window::SetWidthHeight(int width_, int height_)
{
	width = width_;
	height = height_;
}




