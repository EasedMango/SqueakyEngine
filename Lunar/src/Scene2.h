#pragma once
#include "Scene.h"
#include "Actor.h"
#include "SceneManager.h"
class Scene2 :public Scene
{
private:
	class ActorManager* am;

	

public:
	explicit Scene2();

	virtual ~Scene2();

	virtual bool OnCreate() ;
	virtual void OnDestroy() ;
	virtual void Update(const float deltaTime) ;
	virtual void Render() const ;
	virtual void HandleEvents();
	void RenderGui();
};

