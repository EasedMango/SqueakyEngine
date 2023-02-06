#pragma once
#include <Components/Component.h>


class Transform;

class MouseController :
    public Component
{
public:
	MouseController();

	~MouseController() override;
	bool OnCreate() override;
	void OnDestroy() override;
	void Update(const float deltaTime) override;
	void Render() const override;
	void RenderGui() override;

private:
    class Transform* transform;

public:
};

