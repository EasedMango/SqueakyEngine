#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
Camera::Camera(float fov, float ratio) : Component(nullptr) {
	projectionMatrix = glm::perspective(fov, ratio, 0.1f, 100.0f);//(-ratio, ratio, -1.0f, 1.f);
	viewMatrix = glm::lookAt(glm::vec3(0, 0, -5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	//projectionMatrix = glm::translate(projectionMatrix, glm::vec3(0, 0, -10));
}
bool Camera::OnCreate() {

	return true;
}

void Camera::OnDestroy() {}

void Camera::Render() const {}

void Camera::RenderGui()
{
}

void Camera::Update(const float deltaTime) {

}