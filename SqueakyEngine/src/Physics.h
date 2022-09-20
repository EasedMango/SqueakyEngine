#pragma once
#include <vector>
#include "PhysicsBody.h"
#include <map>
#include <tuple>
class Physics
{
private:
	std::vector< PhysicsBody*> bodies;
	int physicsBodies;
	//std::map<std::string, PhysicsBody*> bodies;
	//std::vector< std::string, PhysicsBody*> bodies;
public:


	void const AddBody(PhysicsBody* body);
	std::vector< PhysicsBody*> ReturnBodies() {
		return bodies;
	}
	void const Update(const float deltaTime);



	void const OnDestroy();



	void const RenderGui();
};

