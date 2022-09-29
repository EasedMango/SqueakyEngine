#include "ActorManager.h"
#include "Components/Logger.h"
#include "Components/Camera.h"
#include <imgui.h>
#include "Components/Gui.h"
#include "Physics.h"

ActorManager::ActorManager() {
	physics = new Physics();
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

void ActorManager::DeleteActor(std::string name)
{
	
}

void ActorManager::Update(const float deltaTime) {
	physics->Update(deltaTime);
	for (Actor* a : hierarchy) {
		//for (Actor* c : a->GetChildren()) {
		//	std::cout << c->GetName() << std::endl;
		//}
		a->Update(deltaTime);
		//printf("update");
	}

}

void ActorManager::Render() const {
	for (Actor* a : hierarchy) {
		a->MyRender(mainCamera);
	}


}

void ActorManager::AddActor2(Actor* actor) {
	hierarchy.push_back(actor);
}

void ActorManager::RenderGui() {
	ImGui::Begin("Main Menu");                         
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
	
	ImGui::ListBox("Hierarchy", &current, names.data(), names.size(), 2);
	
	if (ImGui::TreeNode(names[current])) {
		for (auto& a : GetActor(names[current])->GetComponents()) {
			if (ImGui::TreeNode(typeid(*a).name())) {
				a->RenderGui();
				ImGui::TreePop();
			}
		}
		ImGui::TreePop();
	}
	ImGui::End();
	
}
