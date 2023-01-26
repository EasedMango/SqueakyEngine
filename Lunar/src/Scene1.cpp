#include "Scene1.h"
#include "Window.h"
#include "Components/Logger.h"
#include <GLFW/glfw3.h>
#include "Components.h"
#include <glm/ext.hpp>
#include "Scripts/Controller.h"
#include "Scripts/ControllerPhysics.h"
#include "Geometry/BasicShapes.h"
#include "ActorManager.h"
#include "Input.h"
#include "Components/Collider.h"
#include "Scripts/Player.h"
#include "Renderer.h"
#include "Scripts/Spawner.h"
#include "Scripts/ShootWeapons.h"
#include "Audio.h"
#include <Components/Physics/Sphere.h>
#include <Components/Physics/OBB.h>
#include <Audio.h>
Scene1::Scene1()
{
	am = new ActorManager();
	//audio = new Audio();
}


Scene1::~Scene1()
= default;

bool Scene1::OnCreate()
{
	Logger::Info("Creating scene 1");


	am = new ActorManager();
	am->AddActor(new Actor(nullptr, "Camera", new Camera(45.f),
		new Transform(glm::vec3(0.0f, -2.f, -24.0f), glm::vec3(0, 0, 0), glm::vec3(1.0f))));

	//am->AddActor(new Actor(nullptr, "Test",
	//	new Mesh("src/Meshes/Sphere.obj"), new Material("src/Textures/StartMenu.png", "phong"),
	//	new Transform(glm::vec3(4.f, 0.f, 0.f), glm::vec3(0), glm::vec3(1.f)),
	//	new Collider(new Sphere({ 0.f, 0.f, 0.f },{ 1.f})), new PhysicsBody(true)));

	am->AddActor(new Actor(nullptr, "SpaceShip",
		new Mesh("src/Meshes/Sphere.obj"), new Material("src/Textures/StartMenu.png", "phong"),
		new Transform(glm::vec3(4.f, 8.f, 0.f), glm::vec3(0), glm::vec3(1.f)),
		new Collider(new Sphere({ 0.f, 0.f, 0.f }, { 1.f })), new PhysicsBody()));


	am->AddActor(new Actor(nullptr, "CubeTestStatic",
		new Mesh("src/Meshes/Cube.obj"), new Material("src/Textures/StartMenu.png", "phong"),
		new Transform(glm::vec3(-4.f, 8.f, 0.f), glm::vec3(0), glm::vec3(1.f)),
		new Collider(new OBB(1.f, 1.f, 1.f)), new PhysicsBody()));

	am->AddActor(new Actor(nullptr, "Player",
		new Mesh("src/Meshes/Cube.obj"), new Material("src/Textures/StartMenu.png", "phong"),
		new Transform(glm::vec3(-0.f, 0.f, 0.f), glm::vec3(0), glm::vec3(1.f)),
		new Collider(new OBB(1.f, 1.f, 1.f)), new PhysicsBody(), new Controller()));

	//audio->SetListener(am->GetActor("Camera")->GetComponent<Transform>());
//	am->GetActor("Camera")->SetParent(am->GetActor("Player"));
	//audio->PlayAudio("MidstoneJunk.wav", glm::vec3(0));
	Renderer::GetInstance().GetCreateSkybox("src/Textures/StarSkyboxPosx.png", "src/Textures/StarSkyboxPosy.png",
		"src/Textures/StarSkyboxPosz.png", "src/Textures/StarSkyboxNegx.png",
		"src/Textures/StarSkyboxNegy.png", "src/Textures/StarSkyboxNegz.png");
	return false;
}

void Scene1::OnDestroy()
{
	am->OnDestroy();

}

void Scene1::Update(const float deltaTime)
{
	am->Update(deltaTime);
	//audio->Update();
	Renderer::GetInstance().AddText({ "hello",glm::vec3(4,3,5),2 });
}

void Scene1::Render() const
{
	am->Render();
}

void Scene1::HandleEvents()
{
}


void Scene1::RenderGui()
{
	am->RenderGui();
}