#include "Scene2.h"
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
Scene2::Scene2()
{
	am = new ActorManager();
	audio = new Audio();
}


Scene2::~Scene2()
= default;

bool Scene2::OnCreate()
{
	Logger::Info("Creating scene 2");


	am = new ActorManager();
	am->AddActor(new Actor(nullptr, "Camera", new Camera(45.f),
		new Transform(glm::vec3(0.0f, -2.f, -4.0f), glm::vec3(0, 0, 0), glm::vec3(1.0f)), new Spawner(am)));

	am->AddActor(new Actor(nullptr, "SpaceStation",
		new Mesh("src/Meshes/Spacestation.obj"), new Material("src/Textures/SpacestationTexture.png", "phong"),
		new Transform(glm::vec3(9.f, 0.f, 0.f), glm::vec3(0), glm::vec3(1.f)),
		new Collider(new Geometry::Sphere(glm::vec3(0), (0.5f))), new PhysicsBody(true)));

	am->AddActor(new Actor(nullptr, "Player",
		new Mesh("src/Meshes/Spaceship.obj"), new Material("src/Textures/SpaceshipTexture.png", "phong"),
		new Transform(glm::vec3(-3.f, 0.f, 0.f), glm::vec3(0), glm::vec3(1.f)),
		new Collider(new Geometry::Sphere(glm::vec3(0), (0.5f))), new PhysicsBody(),
		new ControllerPhysics(am), new Player(), new ShootWeapons(am)));

	audio->SetListener(am->GetActor("Camera")->GetComponent<Transform>());
	am->GetActor("Camera")->SetParent(am->GetActor("Player"));
	//audio->PlayAudio("MidstoneJunk.wav", glm::vec3(0));
	Renderer::GetInstance().GetCreateSkybox("src/Textures/StarSkyboxPosx.png", "src/Textures/StarSkyboxPosy.png",
		"src/Textures/StarSkyboxPosz.png", "src/Textures/StarSkyboxNegx.png",
		"src/Textures/StarSkyboxNegy.png", "src/Textures/StarSkyboxNegz.png");
	return false;
}

void Scene2::OnDestroy()
{
	am->OnDestroy();

}

void Scene2::Update(const float deltaTime)
{
	am->Update(deltaTime);
	audio->Update();
	Renderer::GetInstance().AddText({ "hello",glm::vec3(4,3,5),2 });
}

void Scene2::Render() const
{
	am->Render();
}

void Scene2::HandleEvents()
{
}


void Scene2::RenderGui()
{
	am->RenderGui();
}
