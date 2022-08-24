#pragma once
#include <string>
class GLFWwindow;
class SceneManager
{
	
private:
	class Scene1* currentScene;
	class Window* window;
	class Events* events;
	double deltaTime;
	double prevTime;
public:
	void Run();
	void HandleEvents(GLFWwindow* window, int key, int scancode, int action, int mods);
	void activate_airship();
	bool Initialize(const char* name_, int width_, int height_);
	//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	
};

