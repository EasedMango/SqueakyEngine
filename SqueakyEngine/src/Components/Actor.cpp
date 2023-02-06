#include "Actor.h"
//#include <glad/glad.h>
#include "Mesh.h"
#include "Camera.h"
#include "Transform.h"
#include "Material.h"
#include <glm/ext.hpp>
#include <Renderer.h>
#include <glm/gtx/string_cast.hpp>
void Actor::SetParent(Actor* parent_)
{
	parent = parent_;
	parent_->AddChild(this);
}

Actor::Actor(const char* name_, Component* parent_) :Component(parent_), name(name_), mesh(nullptr), material(nullptr) {
	static int objctNmbr = 0;
	objctNmbr = 0;
	if (parent_ != nullptr) {
		AddChild(dynamic_cast<Actor*>(parent_));
	}
	if (name == "Actor") {
		name += objctNmbr;
		++objctNmbr;
	}
}

Actor::~Actor() = default;

bool Actor::OnCreate() {
	//	std::cout << name << ":  //////////////////////////////" << std::endl;
	for (const auto component : components) {
		const bool status = component->OnCreate();
		component->SetParent(this);
		//std::cout << typeid(*component).name() << std::endl;
		if (status == false) {
			return false;
		}
		if (typeid(*component) == typeid(Mesh))
			mesh = dynamic_cast<Mesh*>(component);
		if (typeid(*component) == typeid(Material))
			material = dynamic_cast<Material*>(component);
	}
	//	std::cout <<  "  //////////////////////////////" << std::endl;
	return true;
}

void Actor::OnDestroy() {
	RemoveAllComponents();
}

void Actor::Update(const float deltaTime) {
	for (const auto& component : components) {
		component->Update(deltaTime);
	}
}

void Actor::Render() const {



}



void Actor::MyRender() {


	if (mesh == nullptr) {
		//mesh = GetComponent<Mesh>();
		//if (mesh == nullptr)
			return;
	}
	if (material == nullptr) {
		//material = GetComponent<Material>();
		//if (material == nullptr)
			return;
	}

	Renderer::GetInstance().AddToQueue(material->GetShaderFilename(), mesh->GetFilename(), material->GetTextureFilename(), GetComponent<Transform>()->GetTransformMatrix());



}

void Actor::RenderGui()
{
}

std::vector<Component*> Actor::GetComponents() const
{
	std::vector<Component*> componentList;
	for (auto component : components) {
		if (component != nullptr) {
			componentList.push_back(component);
		}
	}
	return componentList;
}

void Actor::ListComponents() const {
	std::cout << typeid(*this).name() << " contain the following components:\n";
	for (auto component : components) {
		std::cout << typeid(*component).name() << std::endl;
	}
}


void Actor::RemoveAllComponents() {
	for (const auto& component : components) {
		component->OnDestroy();
		delete component;
	}
	components.clear();
}

