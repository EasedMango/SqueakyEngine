#pragma once
#include "Body.h"
#include <vector>
class PhysicsEngine
{
	std::vector<Body*> bodies;


	void Update() {
		for (Body* b : bodies) {

		}
	}
};

