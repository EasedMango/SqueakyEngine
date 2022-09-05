#pragma once
#include "Component.h"
class Controller : public Component {


public:
	Controller();
	 ~Controller();
	 bool OnCreate() override;
	 void OnDestroy() override;
	 void Update(const float deltaTime) override;
	 void Render() const override;


};
