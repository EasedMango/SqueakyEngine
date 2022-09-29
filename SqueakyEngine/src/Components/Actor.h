#pragma once
#include <vector>
#include <iostream>
#include "Component.h"
#include <string>
class Camera;
class Actor : public Component
{
	Actor(const Actor&) = delete;
	Actor(Actor&&) = delete;
	Actor& operator= (const Actor&) = delete;
	Actor& operator=(Actor&&) = delete;

private:

	std::vector<Component*> components;
	std::vector<Actor*> children;
	const char* name;

public:
	inline Actor* GetParentActor() {
		return static_cast<Actor*>(parent);
	}
	inline std::vector<Actor*> const GetChildren() {
		return children;
	}
	inline void AddChild(Actor* newChild) { children.push_back(newChild); }
	void SetParent(Actor* parent_);
	Actor(Component* parent_,const char* name_="Actor");
	~Actor();
	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	void MyRender(Actor* cam);
	void RenderGui() override;

	template<typename ComponentTemplate, typename ... Args>
	void AddComponent(Args&& ... args_) {
		ComponentTemplate* componentObject = new ComponentTemplate(std::forward<Args>(args_)...);
		components.push_back(componentObject);

	}

	inline void AddComponent(Component* comp) {
		components.push_back(comp);
	}

	template<typename ComponentTemplate>
	ComponentTemplate* GetComponent() {
		for (auto component : components) {
			if (dynamic_cast<ComponentTemplate*>(component) != nullptr) {
				return dynamic_cast<ComponentTemplate*>(component);
			}
		}
		return nullptr;
	}
	
	std::vector<Component*> GetComponents();

	template<typename ComponentTemplate>
	void RemoveComponent() {
		for (size_t i = 0; i < components.size(); i++) {
			if (dynamic_cast<ComponentTemplate*>(components[i]) != nullptr) {
				components[i]->OnDestroy();
				delete components[i];
				components.erase(components.begin() + i);
				break;
			}
		}
	}


	void ListComponents() const;
	void RemoveAllComponents();


	inline const char* GetName() const { return name; }
	inline void SetName(const char* &name_) { name = name_; }
};

