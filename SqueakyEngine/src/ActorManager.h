#pragma once 
#include "Actor.h"
#include <vector>
#include< stdarg.h >
class ActorManager {
private:
	static int heirarchyLength;
	std::vector<Actor*> hierarchy;
	Actor* mainCamera;
public:
	ActorManager();
	~ActorManager();

	std::vector<Actor*> GetHierarchy() { return hierarchy; }
	bool OnCreate();
	void OnDestroy();
	void Update(const float deltaTime);

	void Render() const;

	template< typename ... C>
	void AddActor(Actor* actor,C&& ... comps) {

		std::vector<Component*> compList = { std::forward<C>(comps)... };
		for (auto component : compList) {
			std::cout << typeid(*component).name() << std::endl;
			actor->AddComponent(component);
		}
		hierarchy.push_back(actor);
		if (actor->GetName() == "Camera")
			mainCamera = actor;

	}

	void key_callback(class GLFWwindow* window, int key, int scancode, int action, int mods);
	void AddActor2(Actor* actor);
	Actor* GetActor(std::string name);
	void DeleteActor(std::string name);
	void RenderGui();
};