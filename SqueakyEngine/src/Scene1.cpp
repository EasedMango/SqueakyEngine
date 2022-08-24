#include "Scene1.h"
#include "Window.h"
#include "Logger.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Mesh.h"
#include "Shader.h"
Scene1::Scene1()
{
}

Scene1::~Scene1()
{
}

bool Scene1::OnCreate()
{
	std::vector<glm::vec3> vertices = { glm::vec3(0.0f, 0.5f,0), glm::vec3(0.5f, -0.5f,0), glm::vec3(-0.5f, -0.5f,0) };
	triangle = new Actor(nullptr);
	Logger::Info("Creating scene 1");
	triangle->AddComponent<Mesh>(nullptr, vertices);
	triangle->AddComponent<Shader>(nullptr, "src/Shaders/defaultVert.glsl", "src/Shaders/defaultFrag.glsl");
	triangle->OnCreate();
	triangle->ListComponents();


	return false;
}

void Scene1::OnDestroy()
{
}

void Scene1::Update(const float deltaTime)
{

}

void Scene1::Render() const
{


	Shader* shader = triangle->GetComponent<Shader>();
	Mesh* mesh = triangle->GetComponent<Mesh>();
	shader->Render();
	mesh->Render();

	glUseProgram(0);
}

void Scene1::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	if (key == GLFW_KEY_TAB && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}
