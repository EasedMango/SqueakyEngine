#include "Scene1.h"
#include "Window.h"
#include "Logger.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Components.h"
#include <glm/ext.hpp>
#include "Scripts/Controller.h"
#include "Geometry/BasicShapes.h"
#include "ActorManager.h"
#include "Scripts/ControllerPhysics.h"
#include "Input.h"

Scene1::Scene1() : am(nullptr)
{
	
}

Scene1::~Scene1()
{
}

bool Scene1::OnCreate()
{
	Logger::Info("Creating scene 1");

	am = new ActorManager();
	am->AddActor(new Actor(nullptr, "Camera"), new Camera(90, 1280.f / 720.f), new Transform(glm::vec3(0.0f, 0, -3.0f)));
	am->AddActor(new Actor(nullptr, "Cube"), new Shader(), new Mesh("src/Meshes/cube.obj"), new Transform(glm::vec3(-0.0f, 0.0f, 0)));
	am->AddActor(new Actor(nullptr, "MarioOne"), new Shader( "phongVert.glsl", "phongFrag.glsl"), new Mesh( "src/Meshes/Mario.obj"), new Material( "src/Textures/mario_main.png"), new Transform(),new PhysicsBody(1,glm::vec3(0.1f,0,0)), new ControllerPhysics());
	//am->AddActor(new Actor(nullptr, "Island"), new Shader(), new Mesh("src/Meshes/islandtestblend.obj"), new Transform(glm::vec3(-0.0f, -1.0f, 0)));

	am->OnCreate();
	//am->GetActor("Cube")->SetParent(am->GetActor("MarioOne"));
	am->GetActor("Camera")->SetParent(am->GetActor("MarioOne"));



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

void Scene1::HandleEvents()
{
}








void Scene1::RenderGui() {
	am->RenderGui();
}