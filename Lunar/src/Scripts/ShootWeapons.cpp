#include "ShootWeapons.h"
#include "ActorManager.h"
#include "Input.h"
#include <GLFW/glfw3.h>
#include "Physics.h"
#include "Components/Material.h"
#include "Components/Mesh.h"
#include "Components/Physics/Sphere.h"
#include "Vec.h"
#include "Missle.h"

ShootWeapons::ShootWeapons(ActorManager* const am) : Component(nullptr), am(am), laser(nullptr)
{
}

bool ShootWeapons::OnCreate()
{

	return true;
}

void ShootWeapons::OnDestroy()
{
}

void ShootWeapons::Update(const float deltaTime)
{
	if (Input::GetInstance().OnClickPress(GLFW_MOUSE_BUTTON_LEFT))
	{
		const Transform* transform = am->GetActor("Camera")->GetComponent<Transform>(); //
		const Transform* transformCam = dynamic_cast<Actor*>(GetParent())->GetComponent<Transform>();
		//Geometry::Ray ray(transform->GetPosition(), transform->GetForward());
		Physics::Rayhit hit;
		am->GetPhysics()->Raycast(transformCam->GetPosition(), -transformCam->GetForward(), hit);
		if (hit.actor != nullptr) {

			std::cout << hit.actor->GetName() << " was hit!\n";
		}
		auto dirGet = transform->GetForward();
		auto dir2 = glm::vec3(-dirGet.x,- dirGet.y,- dirGet.z);
		auto posGet = transformCam->GetWorldPosition();
		auto pos2 = glm::vec3(posGet.x, posGet.y, posGet.z);

		std::cout << transform->GetForward() << std::endl;
		if (hit.actor != nullptr) {
			Actor* a = am->Instantiate(new Actor(nullptr, "Missle", 
				new Mesh("src/Meshes/Missle.obj"), new Material("src/Textures/MissleArnold_diffuse_albedo.png","phong"),
				new Transform(pos2 + dir2, transformCam->GetRotation(), glm::vec3(1.f)),
				new Collider(new Sphere(glm::vec3(0), 0.25f)), new PhysicsBody(false, 1, dir2 * 3.f), new Missle(nullptr, hit.actor, 5.f, 20.f,glm::vec3(0))));

			std::cout << a->GetComponent<Transform>()->GetForward() << std::endl;
		}
		else
			Actor* a = am->Instantiate(new Actor(nullptr, "Missle",
				new Mesh("src/Meshes/Missle.obj"), new Material("src/Textures/MissleArnold_diffuse_albedo.png", "phong"),
				new Transform(pos2 + dir2, transformCam->GetRotation(), glm::vec3(1.f)),
				new Collider(new Sphere(glm::vec3(0), 0.25f)), new PhysicsBody(false, 1, dir2 * 3.f), new Missle(nullptr, nullptr, 5.f, 20.f, dir2)));
		//glm::vec3(transform->GetPosition()), transform->GetRotation());
	}
}

void ShootWeapons::Render() const
{
}

void ShootWeapons::RenderGui()
{
	
}
