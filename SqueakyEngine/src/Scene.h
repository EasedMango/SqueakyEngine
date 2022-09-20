#pragma once
struct GLFWwindow;
class SceneManager;
class Scene {
	
public:
	explicit Scene(){}
	virtual ~Scene() {};

	virtual bool OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void Update(const float deltaTime) = 0;
	virtual void Render() const = 0;
	virtual void HandleEvents() = 0;
	virtual void RenderGui()=0;
};