#pragma once
#include "Scene.h"
#include "Actor.h"
class Scene1 : Scene
{
private:
	Actor* triangle;

public:
	explicit Scene1();
	virtual ~Scene1();

	virtual bool OnCreate() ;
	virtual void OnDestroy() ;
	virtual void Update(const float deltaTime) ;
	virtual void Render() const ;
	virtual void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) ;
};

