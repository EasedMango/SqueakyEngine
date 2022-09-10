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
#include "Input.h"

Scene1::Scene1()
{
	
}

Scene1::~Scene1()
{
}

bool Scene1::OnCreate()
{
	Logger::Info("Creating scene 1");

	am = new ActorManager();

	am->AddActor(new Actor(nullptr, "Camera"), new Camera(40, 1280.f/ 720.f), new Transform(nullptr,glm::vec3(0.0f,0,-3.0f)), new Controller());
	am->AddActor(new Actor(nullptr, "MarioOne"), new Shader(nullptr, "src/Shaders/textureVert.glsl", "src/Shaders/textureFrag.glsl"), new Mesh(nullptr, "src/Meshes/Mario.obj"), new Material(nullptr, "src/Textures/mario_main.png"), new Transform());
	am->OnCreate();





	return false;
}

void Scene1::OnDestroy()
{
}

void Scene1::Update(const float deltaTime)
{
	am->Update(deltaTime);
}

void Scene1::Render() const
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	am->Render();

}








void Scene1::RenderGui() {
	am->RenderGui();
}