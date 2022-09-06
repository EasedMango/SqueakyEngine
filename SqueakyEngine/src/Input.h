#pragma once
#include <queue>
#include <map>
#include <GLFW/glfw3.h>
#include<chrono>
#include <functional>
struct key_event {
	int key, code, action, modifiers;
	std::chrono::steady_clock::time_point time_of_event;
};
class Input
{
private:
    std::map<int, bool> keys;
    std::queue<key_event> unhandled_keys;
    float external_position[2];

    std::map<int, std::function<void(/*args*/)>> key_functions;
public:
    inline void handle_key(GLFWwindow* window, int key, int code, int action, int modifiers) {
        unhandled_keys.emplace(key, code, action, modifiers, std::chrono::steady_clock::now());
    }
    void handle_input(float delta_time);
    void RenderGui();
};