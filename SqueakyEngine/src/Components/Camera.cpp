#include "Camera.h"
#include "Gui.h"
#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>

#include "Renderer.h"

Camera::Camera(const float fov_) : Component(nullptr), fov(fov_), projectionMatrix(), viewMatrix(), camTrn(nullptr)
{
}

void Camera::UpdateViewMatrix()
{
	//if (Actor* parentParent = dynamic_cast<Actor*>(parent)->GetParentActor(); parentParent != nullptr) {

	//	//std::cout << ((Actor*)parent)->GetName() << "'s parent's name is " << parentParent->GetName() << std::endl;
	//	const Transform pmat = *parentParent->GetComponent<Transform>();
	//	//  glm::translate(glm::mat4(1), pos) * glm::inverse(pmat) * glm::scale(glm::mat4(1), scale) * glm::mat4_cast(glm::quat(rotation));
	//	//viewMatrix = ( camTrn->GetTransformMatrix()*glm::inverse( pmat.GetTransformMatrix()));
	//	viewMatrix = (glm::lookAt(camTrn->GetPosition() + pmat.GetPosition(), camTrn->GetPosition() +pmat.GetPosition()+ camTrn->GetForward(), pmat.GetUp()));
	//	return;
	//}
	viewMatrix =  (glm::lookAt(camTrn->GetPosition(), camTrn->GetPosition() + camTrn->GetForward(), glm::vec3(0, 1, 0)));
}



bool Camera::OnCreate() {
	camTrn = dynamic_cast<Actor*>(parent)->GetComponent<Transform>();//glm::ortho(-10.f,10.f,-10.f,10.f,0.01f,1000.f);//
	projectionMatrix =  glm::perspective(fov, (16.0f / 9.0f), 0.5f, 100000.0f);
	UpdateViewMatrix();
	Renderer::GetInstance().SetCamera(GetViewMatrix(), GetProjectionMatrix());
	return true;
}

void Camera::OnDestroy() {}

void Camera::Render() const {}



void Camera::RenderGui()
{
	Gui::GuiM4("Transform: ", GetViewMatrix());
}

glm::mat4 Camera::GetViewMatrix() const
{
	return (camTrn->GetTransformMatrix());

}

void Camera::Update(const float deltaTime) {
	UpdateViewMatrix();
	Renderer::GetInstance().UpdateCamera( camTrn->GetTransformMatrix());
}