#pragma once
#include "Component.h"
#include <glm/matrix.hpp>
#include <glm/ext.hpp>

class Transform : public Component {
private:
	glm::vec3 pos;
	glm::vec3 scale;
	//glm::quat rotation;
	glm::vec3 rotation;
public:
	Transform(Component* parent_=nullptr, glm::vec3 pos_=glm::vec3(0), glm::vec3 orientation_ = glm::vec3(0, 0, 0), glm::vec3 scale_ = glm::vec3(1.0f, 1.0f, 1.0f));
	~Transform();
	bool OnCreate();
	void OnDestroy();
	void Update(const float deltaTime);
	void Render() const;

	glm::vec3 GetPosition() { return pos; }
	glm::vec3 GetScale() { return scale; }
	glm::quat GetRotation() { return glm::quat(rotation); }
	glm::vec3 GetRotationEuler() {
		return rotation;
	}
	glm::mat4 GetTransformMatrix() const;
	void SetTransform(glm::vec3 pos_, glm::vec3 orientation_, glm::vec3 scale_ = glm::vec3(1.0f, 1.0f, 1.0f)) {
		pos = pos_;
		rotation = orientation_;// glm::quat(orientation_);
		//eulerAngles = orientation_;
		scale = scale_;
	}

	void RenderGui();
};