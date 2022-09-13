#include "Actor.h"
#include <glad/glad.h>
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Transform.h"
#include "Material.h"
#include <glm/ext.hpp>

void Actor::SetParent(Actor* parent_)
{
	parent = parent_; 
	parent_->AddChild(this);
}

Actor::Actor(Component* parent_, const char* name_) :Component(parent_), name(name_) {
	static int objctNmbr = 0;
	objctNmbr = 0;
	if (parent_ != nullptr) {
		AddChild((Actor*)parent_);
	}
	if (name == "Actor") {
		name += objctNmbr;
		++objctNmbr;
	}
}

Actor::~Actor() {}

bool Actor::OnCreate() {
	for (auto component : components) {
		bool status = component->OnCreate();
		component->SetParent(this);
		if (status == false) {
			return false;
		}
	}
	return true;
}

void Actor::OnDestroy() {
	RemoveAllComponents();
}

void Actor::Update(const float deltaTime) {
	for (auto& component : components) {
		component->Update(deltaTime);
	}
}

void Actor::Render() const {



}



void Actor::MyRender(Actor* cam) {
	if (GetComponent<Mesh>() == nullptr)
		return;
	Shader* shader = GetComponent<Shader>();
	Material* mat = GetComponent<Material>();

	//MaterialComponent* texture = waluigi->GetComponent<MaterialComponent>();

	glUseProgram(shader->GetProgram());
	cam->GetComponent<Camera>()->SendUniforms(shader);
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, glm::value_ptr(GetComponent < Transform>()->GetTransformMatrix()));
	if (mat != nullptr)
		glBindTexture(GL_TEXTURE_2D, GetComponent<Material>()->getTextureID());
	GetComponent<Mesh>()->Render();
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Actor::RenderGui()
{
}

std::vector<Component*> Actor::GetComponents() {
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
	for (auto component : components) {
		component->OnDestroy();
		delete component;
	}
	components.clear();
}

