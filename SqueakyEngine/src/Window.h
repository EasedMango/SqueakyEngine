#pragma once
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <windows.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
private: 
	 GLFWwindow* window;
	 void* windowPtr;
	 int* height,* width;
	 float ratio;

	 void SetViewport(int width_, int height_);

public:
	Window(const Window&) = delete;
	Window(Window&&) = delete;
	Window& operator=(const Window&) = delete;
	Window& operator=(Window&&) = delete;
	Window();
	Window(int width_, int height_, const char* title);
	void OnDestroy();
	static void SetBuffer(GLFWwindow* window, int width, int height);
	int* GetHeight() { return height; }
	int* GetWidth()  { return width; }
	float GetRatio()  { return ratio; }

	//void OnCreate();

	inline GLFWwindow* GetWindow() { return window; }
	
};

