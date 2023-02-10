#include "Camera.h"
#include "Gui.h"
#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>

#include "Renderer.h"
#include "UBO_Padding.h"

Camera::Camera(const float fov_) : Component(nullptr), RenderCamera(fov_), camTrn(nullptr)
{
	Renderer::GetInstance().SetCamera(this);
}

void Camera::UpdateViewMatrix()
{
	if (camTrn == nullptr) {
		Logger::Error("No Camera Transform Found");
		SetViewMatrix (glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	}
	else {
		glm::quat quaternion = camTrn->GetRotation();
		glm::vec3 position = camTrn->GetPosition();
		SetViewMatrix (glm::mat4(quaternion) * glm::translate(glm::mat4(1), position));
	}
	RenderCamera::UpdateViewMatrix();
	/*viewMatrix =  (glm::lookAt(camTrn->GetPosition(), camTrn->GetPosition() + camTrn->GetForward(), glm::vec3(0, 1, 0)));*/
}


Camera* Camera::GetMainCamera()
{
	return mainCamera;
}


bool Camera::OnCreate() {
	if (isCreated) return true;
	mainCamera = this;
	camTrn = dynamic_cast<Actor*>(parent)->GetComponent<Transform>();
	UpdateProjectionMatrix( (16.0f / 9.0f), 0.5f, 100.0f);
	UpdateViewMatrix();

	isCreated = true;
	return true;
}

void Camera::OnDestroy()
{
	RenderCamera::OnDestroy();

}

void Camera::Render() const
{


}


void Camera::RenderGui()
{
	Gui::GuiM4("Transform: ", GetViewMatrix());
}



void Camera::Update(const float deltaTime) {
	UpdateViewMatrix();
	//Renderer::GetInstance().UpdateCamera(camTrn->GetTransformMatrix());
}