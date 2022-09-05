#pragma once

#include <string>
class Camera;
class GLFWwindow;
class SceneManager
{
	
private:
	class Scene1* currentScene;
	class Window* window;
	class Events* events;
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
	void activate_airship();
	bool Initialize(const char* name_, int width_, int height_);
	//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void SetBuffer(GLFWwindow* window, int width, int height);
};

