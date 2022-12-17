#include "CameraController.h"

#include "Components/Actor.h"
#include "Components/Transform.h"
#include "Components/Camera.h"
#include <Input.h>
CameraController::CameraController(): Component(nullptr)
{
	
}

CameraController::~CameraController()
{
}

bool CameraController::OnCreate()
{
	transform = dynamic_cast<Actor*>(GetParent())->GetComponent<Transform>();
	return true;
}

void CameraController::OnDestroy()
{
}

void CameraController::Update(const float deltaTime)
{
	// Get the homogenous position of the camera and pivot point
	//glm::vec4 position(transform->GetPosition(),1);
	//glm::vec4 pivot(transform->GetPosition()+transform->GetForward(), 1);
	//GLFWvidmode return_struct;
	//
	//glm::vec2 inputSize = Input::GetInstance().GetViewportSize();
	//static glm::vec2 lastMousePos= Input::GetInstance().GetMousePos();
	//glm::vec2 mousePos = Input::GetInstance().GetMousePos();
	//glm::vec3 up = transform->GetUp();
	//if(mousePos== lastMousePos)
	//{
	//	return;
	//}

	//// step 1 : Calculate the amount of rotation given the mouse movement.
	//float deltaAngleX = (2 * glm::pi<float>() / inputSize.x); // a movement from left to right = 2*PI = 360 deg
	//float deltaAngleY = (glm::pi<float>() / inputSize.y);  // a movement from top to bottom = PI = 180 deg
	//float xAngle = (lastMousePos.x - mousePos.x) * deltaAngleX;
	//float yAngle = (lastMousePos.y - mousePos.y) * deltaAngleY;

	//// Extra step to handle the problem when the camera direction is the same as the up vector
	//float cosAngle = glm::dot(transform->GetForward(), up);
	//if (cosAngle * glm::sign(deltaAngleY) > 0.99f)
	//	deltaAngleY = 0;

	//// step 2: Rotate the camera around the pivot point on the first axis.
	//glm::mat4x4 rotationMatrixX(1.0f);
	//rotationMatrixX = glm::rotate(rotationMatrixX, xAngle, up);
	//position = (rotationMatrixX * (position - pivot)) + pivot;

	//// step 3: Rotate the camera around the pivot point on the second axis.
	//glm::mat4x4 rotationMatrixY(1.0f);
	//rotationMatrixY = glm::rotate(rotationMatrixY, yAngle, transform->GetRight());
	//glm::vec3 finalPosition = (rotationMatrixY * (position - pivot)) + pivot;

	//// Update the camera view (we keep the same lookat and the same up vector)
	//transform->SetPosition(finalPosition);

	//// Update the mouse position for the next rotation
	//lastMousePos = mousePos;


}

void CameraController::Render() const
{
}

void CameraController::RenderGui()
{
}
