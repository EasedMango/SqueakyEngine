#pragma once

#include <string>
class Camera;
class GLFWwindow;
class SceneManager
{
	
private:
	class Scene1* currentScene;
	class Window* window;
	//class Input* input;
	class Gui* gui;
	// ImGuiIO* io;
	double curTime;
	double deltaTime;
	double prevTime;
	bool pause;
public:
	SceneManager();
	~SceneManager();
	void Run();
	void RenderGui();
	void HandleEvents(GLFWwindow* window, int key, int scancode, int action, int mods);
	bool Initialize(const char* name_, int width_, int height_);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void SetBuffer(GLFWwindow* window, int width, int height);
};

