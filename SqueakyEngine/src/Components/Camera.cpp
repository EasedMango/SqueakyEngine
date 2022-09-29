#include "Camera.h"
#include "Gui.h"
#include "Transform.h"
#include "Shader.h"
#include <glm/gtc/matrix_transform.hpp>
Camera::Camera(float fov, float ratio) : Component(nullptr) {
	projectionMatrix = glm::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100000.0f);//(-ratio, ratio, -1.0f, 1.f);
	viewMatrix = glm::lookAt(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	//projectionMatrix = glm::translate(projectionMatrix, glm::vec3(0, 0, -10));
}
bool Camera::OnCreate() {

	return true;
}

void Camera::OnDestroy() {}

void Camera::Render() const {}

void Camera::SendUniforms(Shader* shader)
{
	glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(GetProjectionMatrix()));

	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, glm::value_ptr(GetViewMatrix()));
}

void Camera::RenderGui()
{
	Gui::GuiM4("Transform: ", GetViewMatrix());
}

glm::mat4 Camera::GetViewMatrix()
{
	Transform* camTrn = ((Actor*)parent)->GetComponent<Transform>();

	if (camTrn != nullptr)
		return camTrn->GetTransformMatrix();

	else
		return viewMatrix;
}

void Camera::Update(const float deltaTime) {

}