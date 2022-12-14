#include "ActorManager.h"
#include "Components/Logger.h"
#include "Components/Camera.h"
#include <imgui.h>

#include <utility>
#include "Components/Gui.h"
#include "Physics.h"

bool ActorManager::EmptyQueue()
{
	while (!spawnQueue.empty())
	{
		hierarchy.push_back(spawnQueue.front());
		spawnQueue.pop();
	}
	while (!destroyQueue.empty())
	{
		DeleteActor(destroyQueue.front());
		destroyQueue.pop();
	}
	return true;
}

void ActorManager::DeleteActor(Actor* actor)
{

	for (auto i = hierarchy.begin(); i != hierarchy.end(); ++i)
	{
		if (*i == actor)
		{
			physics->RemoveBody(actor->GetComponent<PhysicsBody>());
			actor->OnDestroy();
			hierarchy.erase(i);

			break;
		}
	}

}

ActorManager::ActorManager() : mainCamera(nullptr)
{
	physics = new Physics();
};
ActorManager::~ActorManager() = default;;

bool ActorManager::OnCreate() const
{

	for (Actor* a : hierarchy) {
		a->OnCreate();
	}
	return true;

}
void ActorManager::OnDestroy() const
{

	for (Actor* a : hierarchy) {
		a->OnDestroy();
	}


}

Actor* ActorManager::GetActor(const std::string& name) {
	for (Actor* a : hierarchy) {
		if (a->GetName() == name) {
			return a;

		}
	}

	Logger::Info(name + std::string(" was not found"));
	return nullptr;
}



void ActorManager::DestroyActor(const std::string& name)
{
	destroyQueue.emplace(GetActor(name));
}


void ActorManager::Update(const float deltaTime)
{
	EmptyQueue();
	physics->Update(deltaTime);
	for (Actor* a : hierarchy) {
		if (a == nullptr)
			break;
		a->Update(deltaTime);
	}

}

void ActorManager::Render() const {
	for (Actor* a : hierarchy) {
		a->MyRender();
	}


}

void ActorManager::DestroyActor(Actor* actor)
{

	destroyQueue.emplace(actor);

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
	for (const Actor* a : hierarchy) {
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

	ImGui::ListBox("Hierarchy", &current, names.data(), names.size(), 6);

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
