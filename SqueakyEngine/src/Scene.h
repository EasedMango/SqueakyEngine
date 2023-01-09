#pragma once
#include "Components/Logger.h"
struct GLFWwindow;
class SceneManager;
class Scene {
	
public:
	explicit Scene(){}
	virtual ~Scene() {};

	virtual bool OnCreate() { Logger::Info("Creating SceneOne"); return true; };
	virtual void OnDestroy() = 0;
	virtual void Update(const float deltaTime) = 0;
	virtual void Render() const = 0;
	virtual void HandleEvents() = 0;
	virtual void RenderGui()=0;
};