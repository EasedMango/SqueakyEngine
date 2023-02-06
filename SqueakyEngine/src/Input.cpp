#include <glad/glad.h>
#include "Input.h"
#include <imgui.h>


#define GLFW_INCLUDE_NONE
#include "Vec.h"
#include <glm/geometric.hpp>
#include <glm/ext/matrix_projection.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/geometric.hpp>
#include <glm/gtx/closest_point.hpp>
#include <glm/gtx/intersect.hpp>

#include "Components/Physics/Plane.h"
#include "Components/Physics/Ray.h"
using namespace glm;
//#include "linmath.h"
#define STRING(num) #num

glm::vec3 Input::GetMouseInWorld()
{
	glm::vec3 mousePos(GetMousePos(), 0);
	float x = mousePos.x;
	float y = mousePos.y;
	glm::mat4 proj = Camera::GetMainCamera()->GetProjectionMatrix();

	glm::mat4 view = Camera::GetMainCamera()->GetViewMatrix();

	glm::vec4 viewport(0, 0, GetViewportSize());
	glm::vec4 mousePosNDC = { (mousePos - vec3(viewport.x, viewport.y, 0)) / vec3(viewport.z, viewport.w, 1), 0
	};
	vec4 eyespace = mousePosNDC * inverse(proj);
	vec4 worldspace = eyespace * inverse(view);
	float winX, winY, winZ;               // Holds Our X, Y and Z Coordinates


	winX = (float)x;
	winY = (float)viewport[3] - (float)y;
	winZ = 1.0f;
		//glReadPixels(x, (winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

	vec3 origin = view[3];
		//glm::closestPointOnLine()
	view[3] = { 0,0,view[3].z,view[3].w };
	glm::vec3 worldPosNear = glm::unProject(vec3(winX, winY, 0), view, proj, viewport);
	glm::vec3 worldPosFar = glm::unProject(vec3(winX, winY, 1), view, proj, viewport);
	
	//glm::vec4 myParallelPlaneProjection = (proj * glm::vec4(0, 0, -(worldPosNear + (worldPosFar - worldPosNear) * 0.5f), 1.0f));
	vec4 myParallelPlaneProjection = proj*- vec4(  (worldPosNear + (worldPosFar - worldPosNear) * 0.5f), 1.0f);
	float myParallelPlaneDepth = myParallelPlaneProjection.z / myParallelPlaneProjection.w;

	
	glm::vec3 windows_coords = glm::vec3(winX, winY, myParallelPlaneDepth);
	glm::vec3 position = glm::unProject(windows_coords, view , proj, viewport);
	


	glm::vec3 worldPos = glm::unProject(vec3(winX, winY, 0.975f), view, proj, viewport);
	//position = position;// worldPos.z - 2;
	position = position / (position.z * 10.f);
	float intersectionDistance;
	
	glm::intersectRayPlane({ 0,0,origin .z}, worldPosNear, { 0,0,0 }, vec3(0, 0, 1), intersectionDistance);
	Ray ray({ 0,0,origin.z }, worldPosFar);
	Plane zed(view[1] );


	vec3 point = zed.IntersectionPoint(ray);

	//worldPos.z = ;


	return { -(point.x +origin.x),-(point.y+origin.y),point.z};// origin + intersectionDistance * worldPosNear;// unProject(vec3(winX, winY, winZ), mat4(1), proj, viewport);
}

glm::vec3 Input::GetMouseDepthPosition()
{
	glm::vec3 mousePos(GetMousePos(), 0);
	float x = mousePos.x;
	float y = mousePos.y;
	glm::mat4 proj = Camera::GetMainCamera()->GetProjectionMatrix();

	glm::mat4 view = Camera::GetMainCamera()->GetViewMatrix();

	glm::vec4 viewport(0, 0, GetViewportSize());
	glm::vec4 mousePosNDC = {(mousePos - vec3(viewport.x, viewport.y, 0)) / vec3(viewport.z, viewport.w, 1), 0
};
	vec4 eyespace = mousePosNDC * inverse(proj);
	vec4 worldspace = eyespace * inverse(view);
	float winX, winY, winZ;               // Holds Our X, Y and Z Coordinates


	winX = (float)x;
	winY = (float)viewport[3] - (float)y;
	winZ = 0;
//	glReadPixels(x, (winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

	


	glm::mat4 model = (glm::mat4(1.0f)); // identity matrix



	glm::vec3 worldPos = glm::unProject(vec3(winX, winY, winZ), view, proj, viewport);
	worldPos.z = 0;// worldPos.z - 2;
	return worldPos;// unProject(vec3(winX, winY, winZ), mat4(1), proj, viewport);
}

void Input::HandleInput(float delta_time)
{
	while (!unhandled_keys.empty()) {
		KeyEvent event = unhandled_keys.front();
		unhandled_keys.pop();
		if (keys_.contains(event.key))
			keys_[event.key].Update((bool)event.action);
		else
			keys_[event.key] = Key(event.key, event.code, event.action, event.action);
	}
	while (!unhandled_clicks.empty()) {
		Click event = unhandled_clicks.front();
		unhandled_clicks.pop();
		if (clicks_.contains(event.button))
			clicks_[event.button].Update((bool)event.action);
		else
			clicks_[event.button] = Click(event.button, event.action, event.action,event.mods);
	}

	for (const std::pair<int, Key> &v : keys_)
	{
		Key& ref = keys_[v.first];
		if (ref.state)
		{
			if (ref.timer >= 0.001f)
				ref.Update(1);
			ref.timer += delta_time;
		}
		else
			ref.timer = 0;
	}
	for (const std::pair<int, Click>& v : clicks_)
	{
		Click& ref = clicks_[v.first];
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
	//const ImGuiKey key_first = 0;
	ImGui::Text("Keys down:");
	for (const std::pair<int, Key>& v : keys_)//ImGuiKey key = key_first; key < ImGuiKey_COUNT; key++)
	{
		Key& ref = keys_[v.first];
		//	if (v.second.state)
		//	{


		ImGui::Text("\"%s\" %d (%.02f secs)", glfwGetKeyName(ref.key, ref.code), ref.state, ref.timer);
		ImGui::SameLine();
		const char* str = std::string(" state: " + ref.state).c_str();
		ImGui::Text(str);
		//}
	}
	for (const std::pair<int, Click>& v : clicks_)//ImGuiKey key = key_first; key < ImGuiKey_COUNT; key++)
	{
		Click& ref = clicks_[v.first];
		//	if (v.second.state)
		//	{
		
		//std::string texts = ;
		std::string texts = std::string("Button: " + std::to_string(ref.button)).c_str();
		std::string texts1 = std::string(" State: " + std::to_string(ref.state)).c_str();
		std::string texts2 = std::string(" Timer: " + std::to_string(ref.timer)).c_str();
		const char* text = texts.c_str();
		const char* text1 = texts1.c_str();
			const char* text2 = texts2.c_str();
		ImGui::Text(text);
		ImGui::SameLine();
		ImGui::Text(text1);
		ImGui::SameLine();
		ImGui::Text(text2);

		//const char* str = std::string(" state: " + ref.state).c_str();
		//ImGui::Text(str);
		//}
	}
	//std::cout << "Scrollwheel.x: " << scrollWheel.x << std::endl;
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
	return (keys_.contains(GLFW_key) && keys_[GLFW_key].prevState == false && keys_[GLFW_key].state == true);
}

bool Input::OnKeyHold(int GLFW_key)
{
	return (keys_.contains(GLFW_key) && keys_[GLFW_key].prevState == true && keys_[GLFW_key].state == true);
}

bool Input::OnKeyRelease(int GLFW_key)
{
	return (keys_.contains(GLFW_key) && keys_[GLFW_key].prevState == true && keys_[GLFW_key].state == false);
}
bool Input::OnClickPress(int GLFW_mouse)
{
	return (clicks_.contains(GLFW_mouse) && clicks_[GLFW_mouse].prevState == false && clicks_[GLFW_mouse].state == true);
}

bool Input::OnClickHold(int GLFW_mouse)
{
	return (clicks_.contains(GLFW_mouse) && clicks_[GLFW_mouse].prevState == true && clicks_[GLFW_mouse].state == true);
}

bool Input::OnClickRelease(int GLFW_mouse)
{
	return (clicks_.contains(GLFW_mouse) && clicks_[GLFW_mouse].prevState == true && clicks_[GLFW_mouse].state == false);
}
