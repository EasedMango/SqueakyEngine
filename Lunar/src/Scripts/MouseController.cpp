#include "MouseController.h"
#include <Vec.h>
#include "Input.h"
#include "Components/Actor.h"
#include "Components/Transform.h"

MouseController::MouseController(): Component(nullptr),
                                    transform(nullptr)
{
}

MouseController::~MouseController()
{
}

bool MouseController::OnCreate()
{
	transform = dynamic_cast<Actor*> (GetParent())->GetComponent<Transform>();
	return false;
}

void MouseController::OnDestroy()
{
}

void MouseController::Update(const float deltaTime)
{
	std::cout << Input::GetInstance().GetMouseDepthPosition() << std::endl;
	transform->SetPosition(Input::GetInstance().GetMouseDepthPosition());

}

void MouseController::Render() const
{
}

void MouseController::RenderGui()
{
}
