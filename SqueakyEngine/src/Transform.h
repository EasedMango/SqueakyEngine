#pragma once
#include "Component.h"
#include <glm/matrix.hpp>
#include <glm/ext.hpp>

class Transform : public Component {
private:
	glm::vec3 pos;
	glm::vec3 scale;
	glm::quat rotation;
public:
	Transform(Component* parent_=nullptr, glm::vec3 pos_=glm::vec3(0), glm::quat orientation_ = glm::quat(glm::vec3(0, 0, 0)), glm::vec3 scale_ = glm::vec3(1.0f, 1.0f, 1.0f));
	~Transform();
	bool OnCreate();
	void OnDestroy();
	void Update(const float deltaTime);
	void Render() const;

	glm::vec3 GetPosition() { return pos; }
	glm::vec3 GetScale() { return scale; }
	glm::quat GetOrientation() { return rotation; }

	glm::mat4 GetTransformMatrix() const;
	void SetTransform(glm::vec3 pos_, glm::quat orientation_, glm::vec3 scale_ = glm::vec3(1.0f, 1.0f, 1.0f)) {
		pos = pos_;
		rotation = orientation_;
		scale = scale_;
	}
};