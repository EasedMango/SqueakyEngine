#pragma once
class GLFWwindow;
class Scene {
public:
	Scene(){}
	virtual ~Scene() {};

	virtual bool OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void Update(const float deltaTime) = 0;
	virtual void Render() const = 0;
	virtual void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) = 0;
};