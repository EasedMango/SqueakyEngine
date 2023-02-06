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

	viewMatrix =  (glm::lookAt(camTrn->GetPosition(), camTrn->GetPosition() + camTrn->GetForward(), glm::vec3(0, 1, 0)));
}

Camera* Camera::GetMainCamera()
{ return mainCamera; }


bool Camera::OnCreate() {
	mainCamera =this;
	camTrn = dynamic_cast<Actor*>(parent)->GetComponent<Transform>();
	projectionMatrix =  glm::perspective(fov, (16.0f / 9.0f), 0.1f, 1000.0f);
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