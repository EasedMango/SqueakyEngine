#include "Transform.h"
#include "Gui.h"
#include "Actor.h"
//Transform::Transform() : Component(nullptr)
//{
//}
Transform::Transform( glm::vec3 pos_, glm::vec3 orientation_, glm::vec3 scale_) :Component(nullptr) {

	pos = pos_;
	rotation = glm::radians(orientation_);
	scale = scale_;
}

Transform::~Transform() {
	OnDestroy();
}

bool Transform::OnCreate() {

	return true;
}

void Transform::OnDestroy() {}

void Transform::Render() const {}

void Transform::Update(const float deltaTime) {

}

glm::mat4 Transform::GetTransformMatrix() const {
	Actor* parentParent = ((Actor*)parent)->GetParentActor();
	if (parentParent != nullptr) {
		
		//std::cout << ((Actor*)parent)->GetName() << "'s parent's name is " << parentParent->GetName() << std::endl;
		glm::mat4 pmat = parentParent->GetComponent<Transform>()->GetTransformMatrix();
		return  glm::translate(glm::mat4(1), pos) * glm::inverse(pmat) * glm::scale(glm::mat4(1), scale) * glm::mat4_cast(glm::quat(rotation));
	}
	return glm::translate(glm::mat4(1),pos) * glm::mat4_cast(glm::quat(rotation)) * glm::scale(glm::mat4(1),scale) ;
}

void Transform::RenderGui()
{
	
	Gui::GuiV3("Position", pos);
	Gui::GuiV3("Rotation", rotation);
	Gui::GuiV3("Scale", scale);
}
