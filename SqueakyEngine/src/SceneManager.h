#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Scene.h"
class Camera;
struct GLFWwindow;
class Scene;
class SceneManager
{
	
private:
	Scene* currentScene;
	std::vector<Scene*> scenes;
	class Window* window;
	//class Input* input;
	class ActorManager* actorManager;
	class Gui* gui;
	// ImGuiIO* io;
	double curTime;
	double deltaTime;
	double prevTime;
	bool pause;
public:
	SceneManager();
	~SceneManager();
	void Run(int scene);
	void LoadScene(Scene* scene);
	//template <typename ... C>

	//explicit Actor(Component* parent_, const char* name_ = "Actor", C&& ... comps) : Component(parent_), name(name_)
	//{
	//	for (const std::vector<Component*> compList = { std::forward<C>(comps)... }; auto component : compList)
	//	{
	//		std::cout << typeid(*component).name() << std::endl;

	//		component->SetParent(this);
	//		AddComponent(component);
	//	}

	//}

	Window* GetWindow() const { return window; }

	void AddScene(Scene* scene)
	{
		scenes.push_back(scene);
	}

	void RenderGui();
	void HandleEvents(GLFWwindow* window, int key, int scancode, int action, int mods);
	bool Initialize(const char* name_, int width_, int height_);
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void SetBuffer(GLFWwindow* window, int width, int height);
};

