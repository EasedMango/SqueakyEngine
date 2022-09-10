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
struct key_event {
	int key, code, action, modifiers;
	// float timer;
	std::chrono::steady_clock::time_point time_of_event;
};

struct key {
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

struct click {
	int button;
	int action;
	bool state;
	int mods; 
	bool prevState;

	float timer;
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
	std::map<int, key> keys_;
	std::queue<key_event> unhandled_keys;
	std::map<int, click> clicks_;
	std::queue<click> unhandled_clicks;
	glm::vec2 mousePos;

	//class GLFWwindow* window;

	float external_position[2];

	// std::map<int, std::function<void(/*args*/)>> key_functions;
public:
	inline void SetMousePos(glm::vec2& mp) { mousePos = mp; }
	inline glm::vec2 GetMousePos() { return mousePos; }

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
};