#pragma once
#include <queue>
#include <map>
#include <GLFW/glfw3.h>
#include<chrono>
#include <functional>
#include <iostream>
#include <glm/vec2.hpp>
const enum key_states {
	OnNull = 0, OnPress, OnHold, OnRelease
};
struct KeyEvent {
	int key, code, action, modifiers;
	// float timer;
	std::chrono::steady_clock::time_point time_of_event;
};

struct Key {
	int key, code, action;
	int mods;
	bool state, prevState;

	float timer;
	inline void Update(const int& s) {
		//	if (key == GLFW_KEY_C) {

			//}
		prevState = state;
		state = (s);


	}
};

struct Click {
	int button;
	int action;
	bool state;
	int mods; 
	bool prevState;

	float timer=0;
	inline void Update(const int& s) {
		prevState = state;
		state = (s);
	}
};
static class Input
{
private:
	Input() = default;

	// Delete copy/move so extra instances can't be created/moved.
	Input(const Input&) = delete;
	Input& operator=(const Input&) = delete;
	Input(Input&&) = delete;
	Input& operator=(Input&&) = delete;
	std::map<int, bool> keys;
	std::map<int, Key> keys_;
	std::queue<KeyEvent> unhandled_keys;
	std::map<int, Click> clicks_;
	std::queue<Click> unhandled_clicks;
	glm::vec2 mousePos;
	glm::vec2 prevScrollWheel;
	glm::vec2 scrollWheel;
	glm::vec2 viewportSize;
	//class GLFWwindow* window;

	float external_position[2];

	// std::map<int, std::function<void(/*args*/)>> key_functions;
public:
	inline void SetMousePos(glm::vec2& mp) { mousePos = mp; }
	inline void SetScroll(const float& x, const float& y) { prevScrollWheel = scrollWheel; scrollWheel = glm::vec2(x, y); };
	inline glm::vec2 GetMousePos() { return mousePos; }

	inline void SetViewportSize(int x, int y) { viewportSize = glm::vec2(x, y); }
	inline glm::vec2 GetViewportSize() const { return viewportSize; }

	inline void handle_key(GLFWwindow* window, int key, int code, int action, int modifiers) {

		unhandled_keys.emplace(key, code, action, modifiers, std::chrono::steady_clock::now());
	}
	inline void handle_clicks(GLFWwindow* window, int button, int action, int modifiers) {

		unhandled_clicks.emplace(button, action, action, modifiers);
	}
	static Input* input;
	static Input& GetInstance() {
		// Allocate with `new` in case Singleton is not trivially destructible.
		static Input* singleton = new Input();
		return *singleton;
	}
	void handle_input(float delta_time);
	void RenderGui();

	bool OnKeyPress(int GLFW_key);
	bool OnKeyHold(int GLFW_key);
	bool OnKeyRelease(int GLFW_key);

	bool OnClickPress(int GLFW_mouse);
	bool OnClickHold(int GLFW_mouse);
	bool OnClickRelease(int GLFW_mouse);

	inline float GetScrollWheel() { return scrollWheel.y-prevScrollWheel.y; }
};