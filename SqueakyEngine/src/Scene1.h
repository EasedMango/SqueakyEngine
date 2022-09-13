#pragma once
#include "Scene.h"
#include "Actor.h"
class Scene1 : Scene
{
private:
	class ActorManager* am;
	class Actor* camera;
	class Actor* mario1;
	class Actor* mario2;
	class Triangle* triangle;
	class Camera* cam;
	class Shader* shader;
	

public:
	explicit Scene1();
	virtual ~Scene1();

	virtual bool OnCreate() ;
	virtual void OnDestroy() ;
	virtual void Update(const float deltaTime) ;
	virtual void Render() const ;
	//virtual void HandleEvents();
	void RenderGui();
};

