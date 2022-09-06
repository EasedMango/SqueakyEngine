#include "ActorManager.h"
#include "Logger.h"
#include "Camera.h"
#include <imgui.h>
#include "Gui.h"
#include "Controller.h"

ActorManager::ActorManager() {

};
ActorManager::~ActorManager() {

};

bool ActorManager::OnCreate() {

	for (Actor* a : hierarchy) {
		a->OnCreate();
	}
	return true;

}
void ActorManager::OnDestroy() {

	for (Actor* a : hierarchy) {
		a->OnDestroy();
	}

}

Actor* ActorManager::GetActor(std::string name) {
	for (Actor* a : hierarchy) {
		if (a->GetName() == name) {
			return a;
		}
	}
	Logger::Info(name + std::string(" was not found"));
}

void ActorManager::Update(const float deltaTime) {
	for (Actor* a : hierarchy) {
		a->Update(deltaTime);
	}

}

void ActorManager::Render() const {
	for (Actor* a : hierarchy) {
		a->MyRender(mainCamera->GetComponent<Camera>());
	}


}

void ActorManager::AddActor2(Actor* actor) {
	hierarchy.push_back(actor);
}

void ActorManager::RenderGui() {
	ImGui::Begin("Main Menu");                          // Create a window called "Hello, world!" and append into it.
	//ImGui::
	static int current = 0;
	std::vector<const char*> names;
	const char* name;
	for (Actor* a : hierarchy) {
	//	Logger::Info(a->GetName());
		

		names.push_back(a->GetName());
	}
	const int size = sizeof(hierarchy.data()) / sizeof(hierarchy.data()[0]);
	//std::cout <<(size)<<std::endl;
	const char* a[size];
	for (size_t i = 0; i < size; i++)
	{
		const char* name = hierarchy[i]->GetName();
		a[i] = name;
	}
	
	ImGui::ListBox("Physics Bodies", &current, names.data(), names.size(), 2);
	ImGui::Text(names[current]);

	ImGui::End();
}
void ActorManager::key_callback(class GLFWwindow* window, int key, int scancode, int action, int mods) {
	for (Actor* a : hierarchy) {
		Controller* c = a->GetComponent<Controller>();
		if (c != nullptr) {
			c->HandleKeyEvents(window, key, scancode, action, mods);
		}
	}
}