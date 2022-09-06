#include "Scene1.h"
#include "Window.h"
#include "Logger.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Components.h"
#include <glm/ext.hpp>
#include "Controller.h"
#include "Geometry/BasicShapes.h"
#include "ActorManager.h"

Scene1::Scene1()
{
	triangle = new Triangle();
	shader = new Shader(nullptr, "src/Shaders/defaultVert.glsl", "src/Shaders/defaultFrag.glsl");
}

Scene1::~Scene1()
{
}

bool Scene1::OnCreate()
{
	std::vector<glm::vec3 >verts = {
   glm::vec3(-1.0f, -1.0f, 0.0f),
   glm::vec3(1.0f, -1.0f, 0.0f),
   glm::vec3(0.0f,  1.0f, 0.0f),
	};
	Logger::Info("Creating scene 1");

	am = new ActorManager();

	am->AddActor(new Actor(nullptr, "Camera"), new Camera(60, 16/9), new Transform());
	am->AddActor(new Actor(nullptr, "MarioOne"), new Shader(),new Mesh(nullptr,"src/Meshes/Mario.obj"), new Material(nullptr,"src/Textures/mario_main.png"), new Transform(),new Controller());
	am->OnCreate();








	//camera = new Actor(nullptr,"Camera");
	//camera->AddComponent<Camera>(60, 16 / 9);
	//camera->OnCreate();
	//

	//mario1 = new Actor(nullptr,"MarioOne");
	//mario1->AddComponent<Shader>(nullptr, "src/Shaders/textureVert.glsl", "src/Shaders/textureFrag.glsl");
	//mario1->AddComponent<Mesh>(nullptr, "src/Meshes/Mario.obj");
	//mario1->AddComponent<Transform>(nullptr, glm::vec3(0), glm::quat(glm::vec3(0, 0, 0)));
	//mario1->AddComponent<Material>(nullptr,"src/textures/mario_main.png");
	//mario1->OnCreate();
	//mario2 = new Actor(nullptr,"MarioTwo");
	//mario2->AddComponent<Shader>(nullptr, "src/Shaders/textureVert.glsl", "src/Shaders/textureFrag.glsl");
	//mario2->AddComponent<Mesh>(nullptr, "src/Meshes/Mario.obj");
	//mario2->AddComponent<Transform>(nullptr, glm::vec3(0), glm::quat(glm::vec3(0, 0, 0)));
	//mario2->AddComponent<Material>(nullptr, "src/textures/mario_main.png");
	//mario2->OnCreate();

	
	//std::vector<glm::vec3> vertices = { glm::vec3(0.0f, 0.5f,0), glm::vec3(0.5f, -0.5f,0), glm::vec3(-0.5f, -0.5f,0) };
	//triangle->OnCreate();
	//shader->OnCreate();
	//shader = new Shader(nullptr, "src/Shaders/defaultVert.glsl", "src/Shaders/defaultFrag.glsl");
	//shader->OnCreate();
	//triangle = new Triangle();
	//triangle->OnCreate();
	//triangle->AddComponent<Mesh>(nullptr, "src/Meshes/Mario.obj");




	return false;
}

void Scene1::OnDestroy()
{
}

void Scene1::Update(const float deltaTime)
{
	
	//mario1->GetComponent<Transform>()->SetTransform(glm::vec3(0,0, 0), glm::quat(glm::vec3(0, 0, glfwGetTime())));
	//mario2->GetComponent<Transform>()->SetTransform(glm::vec3(-15.5f, 0, sin(glfwGetTime())), glm::quat(glm::vec3(0, 0, 0)));
}

void Scene1::Render() const
{
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	//glUseProgram(shader->GetProgram());
	am->Render();
	//mario1->MyRender(camera->GetComponent<Camera>());
	//mario2->MyRender(camera->GetComponent<Camera>());
	//glEnable(GL_DEPTH_TEST);
	/// Clear the screen
	//glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glm::mat4 m = glm::mat4(1);
	//glm::rotate(m, (float)glfwGetTime(), glm::vec3(0, 0, 1));
	//glm::mat4 mvp = cam->GetProjectionMatrix() * m;
	//glUseProgram(shader->GetProgram());
	//glUniformMatrix4fv(triangle->GetMvp() , 1, GL_FALSE, glm::value_ptr(mvp));
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	//glUseProgram(0);
}

void Scene1::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	am->key_callback(window, key, scancode, action, mods);
	if (key == GLFW_KEY_TAB && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

}

void Scene1::RenderGui() {
	am->RenderGui();
}