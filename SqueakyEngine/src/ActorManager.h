#pragma once 
#include "Actor.h"
#include <vector>
#include< stdarg.h >
#include "Physics.h"
class ActorManager {
private:
	static int heirarchyLength;
	std::vector<Actor*> hierarchy;
	Actor* mainCamera;
	class Physics* physics;
public:
	ActorManager();
	~ActorManager();

	std::vector<Actor*> GetHierarchy() { return hierarchy; }
	bool OnCreate();
	void OnDestroy();
	void Update(const float deltaTime);

	void Render() const;

	template< typename ... C>
	void AddActor(Actor* actor, C&& ... comps) {

		std::vector<Component*> compList = { std::forward<C>(comps)... };

		for (auto component : compList) {
			std::cout << typeid(*component).name() << std::endl;

			if (typeid(*component) == typeid(PhysicsBody))
				physics->AddBody(static_cast<PhysicsBody*>( component));
			component->SetParent(actor);
			actor->AddComponent(component);
		}

		//actor->SetParent(actor);
		hierarchy.push_back(actor);
		if (actor->GetName() == "Camera")
			mainCamera = actor;

	}


	void AddActor2(Actor* actor);
	Actor* GetActor(std::string name);
	void DeleteActor(std::string name);
	void RenderGui();
};