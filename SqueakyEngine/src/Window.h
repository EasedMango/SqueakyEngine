#pragma once
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <windows.h>
#define GLFW_INCLUDE_NONE
//#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include "Components/Logger.h"
class Window
{
private: 
	 GLFWwindow* window;

	 int height, width;


	

public:
	Window(const Window&) = delete;
	Window(Window&&) = delete;
	Window& operator=(const Window&) = delete;
	Window& operator=(Window&&) = delete;
	Window();
	Window(int width_, int height_, const char* title);
	void OnDestroy() const;
	void SetWidthHeight(int width_, int height_);

	int GetHeight() const { return height; }
	int GetWidth() const { return width; }
	float GetRatio() const { return height/width; }

	//void OnCreate();

	inline GLFWwindow* GetWindow() const { return window; }
	
};

