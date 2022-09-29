#pragma once
#include "Scene.h"
#include "Components/Actor.h"
class Scene1 :public  Scene
{
private:
	class ActorManager* am;

	

public:
	explicit Scene1();
	virtual ~Scene1();

	virtual bool OnCreate() ;
	virtual void OnDestroy() ;
	virtual void Update(const float deltaTime) ;
	virtual void Render() const ;
	virtual void HandleEvents();
	virtual void RenderGui();
};

