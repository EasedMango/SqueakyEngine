#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>

#include "Window.h"
class Gui
{
private:
	


	ImGuiIO* gui;
	Window* parent;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	ImGuiWindowFlags window_flags = 0;
public:

	Gui();
	Gui(const int width, const float height);
	Gui(Window* wind);
	inline ImGuiIO* ReturnGuiIO() {
		return gui;
	}
	static void  GuiV3(const char* t, glm::vec3& v);

	static void GuiM4(const char* t, glm::mat4& m);

	void Destroy();

	void Rest() ;


	void Render();
	bool OnCreate();
};

