#include "Transform.h"
#include "Gui.h"
#include "Actor.h"
//Transform::Transform() : Component(nullptr)
//{
//}
using namespace glm;
Transform::Transform(vec3 pos_, quat orientation_, vec3 scale_) :Component(nullptr) {

	pos = pos_;
	rotation = (orientation_);
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

glm::vec3 Transform::GetWorldPosition() const
{
	if (Actor* parentParent = dynamic_cast<Actor*>(parent)->GetParentActor(); parentParent != nullptr) {

		//std::cout << ((Actor*)parent)->GetName() << "'s parent's name is " << parentParent->GetName() << std::endl;

	
		return pos + parentParent->GetComponent<Transform>()->GetPosition();

	}
	return pos;
}

void Transform::Update(const float deltaTime) {

}

inline mat4 Transform::TranslateMatrix() const
{
	return mat4(translate(mat4(1), pos) * mat4_cast((rotation)));
}

mat4 Transform::GetTransformMatrix(const bool local) const {
	if (Actor* parentParent = dynamic_cast<Actor*>(parent)->GetParentActor(); parentParent != nullptr) {

		//std::cout << ((Actor*)parent)->GetName() << "'s parent's name is " << parentParent->GetName() << std::endl;

		const glm::mat4 pmat = parentParent->GetComponent<Transform>()->GetTransformMatrix();
		return  glm::translate(glm::mat4(1), pos) * glm::inverse(pmat)  * glm::mat4_cast(glm::quat(rotation));
	
	}
	return TranslateMatrix();
}



void Transform::RenderGui()
{
	//Gui::GuiM4("Matrix", GetTransformMatrix());

	vec3 forward = GetForward();
	Gui::GuiV3("Forward",forward );

	vec3 right = GetRight();
	Gui::GuiV3("Right", right);

	vec3 up = GetUp();
	Gui::GuiV3("Up", up);

	Gui::GuiV3("Position", pos);
	vec3 qua = degrees(eulerAngles(rotation));
	Gui::GuiV3("Rotation", qua);
	rotation = radians(qua);
	Gui::GuiV3("Scale", scale);


}
