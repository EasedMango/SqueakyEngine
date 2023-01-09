#pragma once
#include <vector>
#include <iostream>
#include "Component.h"
#include <string>
#include "Logger.h"
class Camera;
class Actor : public Component
{
	Actor(const Actor&) = delete;
	Actor(Actor&&) = delete;
	Actor& operator= (const Actor&) = delete;
	Actor& operator=(Actor&&) = delete;

private:
	friend class ActorManager;
	std::vector<Component*> components;
	std::vector<Actor*> children;
	const char* name;
	class Mesh* mesh;
	class Material* material;
	int id{};


public:
	inline Actor* GetParentActor() const
	{
		return dynamic_cast<Actor*>(parent);
	}
	inline std::vector<Actor*> GetChildren()
	{
		return children;
	}
	inline void AddChild(Actor* newChild) { children.push_back(newChild); }
	void SetParent(Actor* parent_);
	explicit Actor(const char* name_ = "Actor", Component* parent_ = nullptr);
	~Actor() override;
	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;

	int GetID() { return id; }
	void MyRender();
	void RenderGui() override;

	template <typename ... C>
	explicit Actor(Component* parent_, const char* name_ = "Actor", C&& ... comps) : Component(parent_), name(name_)
	{
		for (const std::vector<Component*> compList = { std::forward<C>(comps)... }; auto component : compList)
		{
			std::cout << typeid(*component).name() << std::endl;

			component->SetParent(this);
			AddComponent(component);
		}

	}

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
		Logger::Info(std::string(name).append(std::string(" Component Not Found ").append(typeid(ComponentTemplate).name())));
		return nullptr;
	}

	std::vector<Component*> GetComponents() const;

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
	inline void SetName(const char*& name_) { name = name_; }
};

