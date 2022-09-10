#include "Actor.h"
#include <glad/glad.h>
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Transform.h"
#include "Material.h"
#include <glm/ext.hpp>

Actor::Actor(Component* parent_, const char* name_) :Component(parent_),name(name_) {
	static int objctNmbr=0;
	objctNmbr = 0;
	if (name == "Actor") {
		name += objctNmbr;
		++objctNmbr;
	}
}

Actor::~Actor() {}

bool Actor::OnCreate() {
	for (auto component : components) {
		bool status = component->OnCreate();
		component->SetParent( this);
		if (status == false) {
			return false;
		}
	}
	return true;
}

void Actor::OnDestroy() {
}

void Actor::Update(const float deltaTime) {
	for (auto &component : components) {
		component->Update(deltaTime);
	}
}

void Actor::Render() const {


	
}



void Actor::MyRender( Actor* cam) {
	if (GetComponent<Mesh>() == nullptr)
		return;
	Shader* shader = GetComponent<Shader>();
	Camera* camCmp = cam->GetComponent<Camera>();
	Transform* camTrn = cam->GetComponent<Transform>();

	//MaterialComponent* texture = waluigi->GetComponent<MaterialComponent>();

	glUseProgram(shader->GetProgram());
	glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(camCmp->GetProjectionMatrix()));
	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, glm::value_ptr(camTrn->GetTransformMatrix()*glm::translate(glm::mat4(1),glm::vec3(0,0,10))));
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, glm::value_ptr(GetComponent < Transform>()->GetTransformMatrix()));
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

