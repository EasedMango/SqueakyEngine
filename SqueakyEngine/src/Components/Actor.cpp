#include "Actor.h"
#include <glad/glad.h>
#include "Mesh.h"
#include "Shader.h"
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

Actor::Actor(Component* parent_, const char* name_) :Component(parent_), name(name_) {
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
	std::cout << name << ":  //////////////////////////////" << std::endl;
	for (const auto component : components) {
		const bool status = component->OnCreate();
		component->SetParent(this);
		std::cout << typeid(*component).name() << std::endl;
		if (status == false) {
			return false;
		}
	}
	std::cout <<  "  //////////////////////////////" << std::endl;
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




	std::string meshName;
	if (const Mesh* mesh = GetComponent<Mesh>(); mesh != nullptr)
	{
		meshName = mesh->GetFilename();

	}
	else
	{
		return;
	}

	std::string materialName;
	if (const Material* material = GetComponent<Material>(); material != nullptr)
	{
		materialName = material->GetFilename();

	}
	else
		return;

	std::string vert, frag;

	if (const Shader* shader = GetComponent<Shader>(); shader != nullptr)
	{
		vert = shader->GetFilenameV();
		frag = shader->GetFilenameF();
	}
	else return;


	const glm::mat4 matrix = GetComponent<Transform>()->GetTransformMatrix();

	//std::cout << glm::to_string(*matrix) << std::endl;
	Renderer::GetInstance().AddToQueue(vert, frag, meshName, materialName, GetComponent<Transform>()->GetTransformMatrix());



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

