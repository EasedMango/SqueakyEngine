#pragma once 
#include "Components/Actor.h"
#include <vector>
#include "Renderer.h"
#include "Physics.h"
#include "Components/Camera.h"

class ActorManager {
private:
	static int heirarchyLength;
	std::vector<Actor*> hierarchy;
	std::queue<Actor*> spawnQueue;
	std::queue<Actor*> destroyQueue;
	Actor* mainCamera;
	class Physics* physics;
	bool EmptyQueue();
public:
	ActorManager();
	~ActorManager();
	inline Physics* GetPhysics() { return physics; }
	std::vector<Actor*> GetHierarchy() { return hierarchy; }
	bool OnCreate() const;
	void OnDestroy() const;
	void Update(const float deltaTime) ;

	void Render() const;
	Actor* GetCamera() { return mainCamera; }
	//template <typename ... C>
	//Actor* Instantiate(Actor* actor, C&& ... comps) {
	//	for (const std::vector<Component*> compList = { std::forward<C>(comps)... }; const auto component : compList)
	//	{
	//		component->SetParent(actor);
	//		actor->AddComponent(component);
	//	}
	//	actor->OnCreate();
	//	for (auto* component : actor->GetComponents()) {
	//		

	//		if (typeid(*component) == typeid(PhysicsBody))
	//			physics->AddBody(dynamic_cast<PhysicsBody*>(component));
	//		if (typeid(*component) == typeid(Camera)) {
	//			mainCamera = actor;
	//			Renderer::GetInstance().SetCamera(actor->GetComponent<Camera>()->GetViewMatrix(), actor->GetComponent<Camera>()->GetProjectionMatrix());
	//		}
	//	}
	//	//actor->SetParent(actor);
	//	spawnQueue.emplace(new Actor(actor));
	//	if (actor->GetName() == "Camera") {
	//		mainCamera = actor;
	//		Renderer::GetInstance().SetCamera(actor->GetComponent<Camera>()->GetViewMatrix(), actor->GetComponent<Camera>()->GetProjectionMatrix());
	//	}

	//	return actor;
	//}
	Actor* Instantiate(Actor* actor) {
		
		for (auto* component : actor->GetComponents()) {


			if (typeid(*component) == typeid(PhysicsBody))
				physics->AddBody(dynamic_cast<PhysicsBody*>(component));

		}
		actor->OnCreate();
		if (actor->GetName() == "Camera") {
			mainCamera = actor;
			Renderer::GetInstance().SetCamera(actor->GetComponent<Camera>()->GetViewMatrix(), actor->GetComponent<Camera>()->GetProjectionMatrix());
		}
		//actor->SetParent(actor);
		spawnQueue.emplace(actor);
		return actor;
	}

	Actor* Instantiate(Actor* actor, glm::vec3 pos,glm::quat rot=glm::quat(0,1,0,0)) {
		
		for (auto* component : actor->GetComponents()) {
			if (typeid(*component) == typeid(Transform)) {
				(dynamic_cast<Transform*>(component))->SetPosition(pos);
				(dynamic_cast<Transform*>(component))->SetRotation(rot);
			}
			if (typeid(*component) == typeid(PhysicsBody))
				physics->AddBody(dynamic_cast<PhysicsBody*>(component));

		}
		actor->OnCreate();
		if (actor->GetName() == "Camera") {
			mainCamera = actor;
			Renderer::GetInstance().SetCamera(actor->GetComponent<Camera>()->GetViewMatrix(), actor->GetComponent<Camera>()->GetProjectionMatrix());
		}
		//actor->SetParent(actor);
		spawnQueue.emplace(actor);
		return actor;
	}
	
	void AddActor(Actor* actor) {
	
		
		for (auto* component : actor->GetComponents()) {


			if (typeid(*component) == typeid(PhysicsBody))
				physics->AddBody(dynamic_cast<PhysicsBody*>(component));

		}
		actor->OnCreate();
		if (actor->GetName() == "Camera") {
			mainCamera = actor;
			Renderer::GetInstance().SetCamera(actor->GetComponent<Camera>()->GetViewMatrix(), actor->GetComponent<Camera>()->GetProjectionMatrix());
		}
		hierarchy.push_back(actor);
	}
	

	void AddActor2(Actor* actor);
	Actor* GetActor(std::string name);
	void DeleteActor(std::string name);
	void DestroyActor(std::string name);
	void RenderGui();
};



