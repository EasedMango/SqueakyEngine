#include "Input.h"
#include <imgui.h>
void Input::handle_input(float delta_time)
{
	//Anything that should happen "when the users presses the key" should happen here
	while (!unhandled_keys.empty()) {
		key_event event = unhandled_keys.front();
		unhandled_keys.pop();
		if (keys_.contains(event.key))
			keys_[event.key].Update((bool)event.action);
		else
			keys_[event.key] = key(event.key, event.code, event.action, event.action);
		//   key_functions[event.key](/*args*/);
		//keys[event] = event.action == GLFW_PRESS || event.action == GLFW_REPEAT;
		//keys.emplace_back(event.key, event.code, event.action, event.modifiers, 0, std::chrono::steady_clock::now());
	}
	while (!unhandled_clicks.empty()) {
		click event = unhandled_clicks.front();
		unhandled_clicks.pop();
		if (clicks_.contains(event.button))
			clicks_[event.button].Update((bool)event.action);
		else
			clicks_[event.button] = click(event.button, event.action, event.action,event.mods);
	}
	for (const std::pair<int, key> &v : keys_)
	{
		key& ref = keys_[v.first];
		if (ref.state)
		{
			if (ref.timer >= 0.001f)
				ref.Update(1);
			ref.timer += delta_time;
		}
		else
			ref.timer = 0;
	}
	for (const std::pair<int, click>& v : clicks_)
	{
		click& ref = clicks_[v.first];
		if (ref.state)
		{
			if (ref.timer >= 0.001f)
				ref.Update(1);
			ref.timer += delta_time;
		}
		else
			ref.timer = 0;
	}
}

void Input::RenderGui()
{
	ImGui::Begin("Keys");



	const int currentItem = 0;
	// ImGui::ListBox();
	const ImGuiKey key_first = 0;
	ImGui::Text("Keys down:");
	for (const std::pair<int, key>& v : keys_)//ImGuiKey key = key_first; key < ImGuiKey_COUNT; key++)
	{
		key& ref = keys_[v.first];
		//	if (v.second.state)
		//	{


		ImGui::Text("\"%s\" %d (%.02f secs)", glfwGetKeyName(ref.key, ref.code), ref.state, ref.timer);
		ImGui::SameLine();
		const char* str = std::string(" state: " + ref.state).c_str();
		ImGui::Text(str);
		//}
	}
	for (const std::pair<int, click>& v : clicks_)//ImGuiKey key = key_first; key < ImGuiKey_COUNT; key++)
	{
		click& ref = clicks_[v.first];
		//	if (v.second.state)
		//	{


		ImGui::Text("\"%s\" %d (%.02f secs)", ref.button, ref.state, ref.timer);
		ImGui::SameLine();
		const char* str = std::string(" state: " + ref.state).c_str();
		ImGui::Text(str);
		//}
	}
	ImGui::End();
	//ImGui::Text("Keys pressed:");
	//for (ImGuiKey key = key_first; key < ImGuiKey_COUNT; key++) { if (ImGui::IsKeyPressed(key)) { ImGui::SameLine(); ImGui::Text("\"%s\" %d", ImGui::GetKeyName(key), key); } }
	//ImGui::Text("Keys released:");
	//for (ImGuiKey key = key_first; key < ImGuiKey_COUNT; key++) { if (ImGui::IsKeyReleased(key)) { ImGui::SameLine(); ImGui::Text("\"%s\" %d", ImGui::GetKeyName(key), key); } }
	// ImGui::Text("Keys mods: %s%s%s%s", ImGui.KeyCtrl ? "CTRL " : "", io.KeyShift ? "SHIFT " : "", io.KeyAlt ? "ALT " : "", io.KeySuper ? "SUPER " : "");
   //  ImGui::Text("Chars queue:");        for (int i = 0; i < io.InputQueueCharacters.Size; i++) { ImWchar c = io.InputQueueCharacters[i]; ImGui::SameLine();  ImGui::Text("\'%c\' (0x%04X)", (c > ' ' && c <= 255) ? (char)c : '?', c); } // FIXME: We should convert 'c' to UTF-8 here but the functions are not public.


}

bool Input::OnKeyPress(int GLFW_key)
{
	
	if (keys_.contains(GLFW_key) && keys_[GLFW_key].prevState == false && keys_[GLFW_key].state == true) {
		printf("OnPress\n");
		return true;
	}
	return false;
}

bool Input::OnKeyHold(int GLFW_key)
{
	if (keys_.contains(GLFW_key) && keys_[GLFW_key].prevState == true && keys_[GLFW_key].state == true) {
		keys_[GLFW_key].Update(1);
		printf("OnHold\n");
		return true;
	}
	return false;
}

bool Input::OnKeyRelease(int GLFW_key)
{
	if (keys_.contains(GLFW_key) && keys_[GLFW_key].prevState == true && keys_[GLFW_key].state == false) {
		keys_[GLFW_key].Update(0);
		printf("OnRelease\n");
		return true;
	}
	return false;
}
