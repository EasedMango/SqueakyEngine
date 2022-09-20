#pragma once
#include <Scene.h>
class Scene0
{

private:

public:
	explicit Scene0();
	virtual ~Scene0();

	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Update(const float deltaTime);
	virtual void Render() const;
	virtual void HandleEvents();
	virtual void RenderGui();
};

