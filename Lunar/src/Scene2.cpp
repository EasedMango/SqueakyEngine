#include "Scene2.h"
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
#include "Input.h"
#include "Geometry/BasicShapes.h"

Scene2::Scene2()
{
	am = new ActorManager();
}



Scene2::~Scene2()
{
}

bool Scene2::OnCreate()
{
	Logger::Info("Creating scene 2");

	
	am = new ActorManager();
	am->AddActor(new Actor(nullptr, "Camera"), new Camera(90, 1280.f / 720.f), new Transform(glm::vec3(0.0f, 10.0f, -80.0f)));
	am->AddActor(new Actor(nullptr, "Mario"), new Shader("phongVert.glsl", "phongFrag.glsl"), new Mesh("src/Meshes/Mario.obj"), new Material("src/Textures/SpaceShip.jpg"), new Transform(glm::vec3(0.0f, 0.0f, 0), glm::vec3(-0.0f, 0.0f, 0), glm::vec3(-0.5f)));
	//am->AddActor(new Actor(nullptr, "Normandy"), new Shader("phongVert.glsl", "phongFrag.glsl"), new Mesh("src/Meshes/Normandy.obj"), new Material("src/Textures/NR2_InGame.png"), new Transform(glm::vec3(-2.0f, 0.0f, 0), glm::vec3(-90.0f, 0.0f, 0),glm::vec3(0.001f)), new Controller);
	//am->AddActor(new Actor(nullptr, "Island"), new Shader(), new Mesh("src/Meshes/islandtestblend.obj"), new Transform(glm::vec3(-0.0f, -1.0f, 0)));

	am->OnCreate();
	//am->GetActor("Cube")->SetParent(am->GetActor("MarioOne"));
	//am->GetActor("Camera")->SetParent(am->GetActor("Normandy"));
	//am->GetActor("Camera")->SetParent(am->GetActor("MarioOne"));



	return false;
}

void Scene2::OnDestroy()
{
}

void Scene2::Update(const float deltaTime)
{
	am->Update(deltaTime);
}

void Scene2::Render() const
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	am->Render();

}

void Scene2::HandleEvents()
{
}








void Scene2::RenderGui() {
	am->RenderGui();
}