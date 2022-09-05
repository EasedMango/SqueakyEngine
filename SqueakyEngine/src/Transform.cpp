#include "Transform.h"

Transform::Transform(Component* parent_, glm::vec3 pos_, glm::quat orientation_, glm::vec3 scale_) :Component(parent_) {

	pos = pos_;
	rotation = orientation_;
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
	return glm::translate(glm::mat4(1),pos) * glm::scale(glm::mat4(1),scale) * glm::mat4_cast(rotation);
}