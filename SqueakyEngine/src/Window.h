#pragma once
#include <windows.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
class Window
{
private: 
	 GLFWwindow* window;
	 void* windowPtr;

public:
	Window(const Window&) = delete;
	Window(Window&&) = delete;
	Window& operator=(const Window&) = delete;
	Window& operator=(Window&&) = delete;
	Window();
	Window(int width, int height, const char* title);

	//void OnCreate();

	inline GLFWwindow* GetWindow() { return window; }
	
};

