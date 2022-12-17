#include "Spawner.h"
#include "ActorManager.h"
#include "Input.h"
#include <GLFW/glfw3.h>
#include "Enemy.h"

#include "Components/Material.h"
#include "Components/Mesh.h"
#include "Components/Shader.h"


Spawner::Spawner(ActorManager* am): Component(nullptr), am(am)
{
}

bool Spawner::OnCreate()
{
	srand(time(0));
	return true;
}

void Spawner::OnDestroy()
{
}

void Spawner::Update(const float deltaTime)
{
	timer += deltaTime;

	static int pos = 0;
	if (timer >= 3.f)
	{
		timer = 0.f;

		am->Instantiate(new Actor(nullptr, "UFO", new Shader("phongVert.glsl", "phongFrag.glsl"),
			new Mesh("src/Meshes/UFO.obj"), new Material("src/Textures/UFOTexture.png"),
			new Transform(glm::vec3(-100.f, 0.f, rand() % 100), glm::vec3(0), glm::vec3(1.f)),
			new Collider(new Geometry::Sphere(glm::vec3(0), (0.5f))), new PhysicsBody(), new Enemy(am)));
	}
}

void Spawner::Render() const
{
}

void Spawner::RenderGui()
{
}
