#include "Input.h"

void Input::handle_input(float delta_time)
{
    //Anything that should happen "when the users presses the key" should happen here
    while (!unhandled_keys.empty()) {
        key_event event = unhandled_keys.front();
        unhandled_keys.pop();
        //   key_functions[event.key](/*args*/);
        keys[event.key] = event.action == GLFW_PRESS || event.action == GLFW_REPEAT;
    }
    //Anything that should happen "while the key is held down" should happen here.
    float movement[2] = { 0,0 };
    if (keys[GLFW_KEY_W]) movement[0] += delta_time;
    if (keys[GLFW_KEY_S]) movement[0] -= delta_time;
    if (keys[GLFW_KEY_A]) movement[1] -= delta_time;
    if (keys[GLFW_KEY_D]) movement[1] += delta_time;
    external_position[0] += movement[0];
    external_position[1] += movement[1];
}

void Input::RenderGui()
{
}
