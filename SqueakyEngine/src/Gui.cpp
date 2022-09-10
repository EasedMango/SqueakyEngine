#include "Gui.h"
#include "imconfig.h"
#include <glm/vec3.hpp>
#include <string>
#include <iostream>
#include "Actor.h"
#include "Components.h"
Gui::Gui()
{
}

Gui::Gui(const int width, const float height) :gui(nullptr)
{
	parent = new Window();

}

Gui::Gui(Window* wind) :gui(nullptr)
{
	parent = wind;
}



void Gui::GuiV3(const char* t, glm::vec3& v)
{

	std::string tt = (std::string(" x ") + std::to_string(v.x) + std::string(" y ") + std::to_string(v.y) + std::string(" z ") + std::to_string(v.z));
	const char* ttt = tt.c_str();
	//printf(ttt);



	if (ImGui::TreeNode(t)) {
		ImGui::SameLine();
		ImGui::Text(ttt);
		ImGui::Text("      x"); ImGui::SameLine(); ImGui::Text("            y"); ImGui::SameLine(); ImGui::Text("            z");
		//glm::vec3 xyz = v;
		ImGui::DragFloat3("x", &v[0], 0.005f);
		ImGui::NewLine();
		ImGui::TreePop();
	}
	else {
		ImGui::SameLine();
		ImGui::Text(ttt);
	}


	/*v=(xyz);*/
}
void Gui::GuiQuat(const char* t, glm::quat& v)
{

	std::string tt = (std::string(" x ") + std::to_string(v.x) + std::string(" y ") + std::to_string(v.y) + std::string(" z ") + std::to_string(v.z) + std::string(" w ") + std::to_string(v.w));
	const char* ttt = tt.c_str();
	//printf(ttt);



	if (ImGui::TreeNode(t)) {
		ImGui::SameLine();
		ImGui::Text(ttt);
		ImGui::Text("      x"); ImGui::SameLine(); ImGui::Text("            y"); ImGui::SameLine(); ImGui::Text("            z"); ImGui::SameLine(); ImGui::Text("            w");
		//glm::vec3 xyz = v;
		ImGui::DragFloat4("", &v[0], 0.005f);
		ImGui::NewLine();
		ImGui::TreePop();
	}
	else {
		ImGui::SameLine();
		ImGui::Text(ttt);
	}


	/*v=(xyz);*/
}
void Gui::GuiM4(const char* t, glm::mat4& m)
{
	//std::string tt = (std::string(" x ") + std::to_string(v.x) + std::string(" y ") + std::to_string(v.y) + std::string(" z ") + std::to_string(v.z));
	//const char* ttt = tt.c_str();
	//printf(ttt);

	ImGui::InputFloat4("m", &m[0][0]);
	ImGui::InputFloat4("m", &m[1][0]);
	ImGui::InputFloat4("m", &m[2][0]);
	ImGui::InputFloat4("m", &m[3][0]);

	//if (ImGui::TreeNode(t)) {
	//	ImGui::SameLine();
	//	ImGui::Text(ttt);
	//	ImGui::Text("      x"); ImGui::SameLine(); ImGui::Text("            y"); ImGui::SameLine(); ImGui::Text("            z");
	//	//glm::vec3 xyz = v;
	//	ImGui::DragFloat3("x", &v[0], 0.005f);
	//	ImGui::NewLine();
	//	ImGui::TreePop();
	//}
	//else {
	//	ImGui::SameLine();
	//	ImGui::Text(ttt);
	//}
}
void Gui::GuiComponents(Actor* actor)
{
	for (auto* comp : actor->GetComponents()) {

	}
	
}
;

void Gui::Destroy()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void Gui::Rest()
{
	if (gui != nullptr) {
		Destroy();
		OnCreate();
	}
	else {
		std::cout << "Can't reset, gui is nullptr\n";
	}
}

void Gui::Render()
{

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}



bool Gui::OnCreate()
{


	// Setup Dear ImGui context
	//const char* glsl_version = "#version 130";
	//IMGUI_CHECKVERSION();
	//ImGui::CreateContext();
	//gui = &ImGui::GetIO(); (void)gui;
	//// Setup Dear ImGui style
	//ImGui::StyleColorsDark();
	////ImGui::StyleColorsClassic();
	//SDL_GLContext gl_context = SDL_GL_CreateContext(parent->getWindow());
	//// Setup Platform/Renderer backends
	//ImGui_ImplSDL2_InitForOpenGL(parent->getWindow(), gl_context);
	//ImGui_ImplOpenGL3_Init(glsl_version);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	gui = &ImGui::GetIO(); (void)gui;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(parent->GetWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 450");
	return true;
}