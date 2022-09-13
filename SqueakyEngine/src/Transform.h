#pragma once
#include "Component.h"
#include <glm/matrix.hpp>
#include <glm/ext.hpp>
#include "Components.h"
class Transform : public Component {
private:

	glm::vec3 pos;
	glm::vec3 scale;
	//glm::quat rotation;
	glm::vec3 rotation;
public:
	Transform(glm::vec3 pos_=glm::vec3(0), glm::vec3 orientation_ = glm::vec3(0, 0, 0), glm::vec3 scale_ = glm::vec3(1.0f, 1.0f, 1.0f));
	~Transform();
	bool OnCreate();
	void OnDestroy();
	void Update(const float deltaTime);
	void Render() const;

	inline glm::vec3 GetPosition() { return pos; }
	inline glm::vec3 GetScale() { return scale; }
	inline glm::quat GetRotation() { return glm::quat(rotation); }
	inline glm::vec3 GetRotationEuler() {
		return rotation;
	}
	inline glm::vec3 GetForward() { return glm::inverse(GetTransformMatrix())[2]; }
	inline glm::vec3 GetRight() { return glm::inverse(GetTransformMatrix())[0]; }
	inline glm::vec3 GetUp() { return glm::inverse(GetTransformMatrix())[1]; }
	glm::mat4 GetTransformMatrix() ;
	inline void SetTransform(glm::vec3 pos_, glm::vec3 orientation_, glm::vec3 scale_ = glm::vec3(1.0f, 1.0f, 1.0f)) {
		pos = pos_;
		rotation = orientation_;// glm::quat(orientation_);
		//eulerAngles = orientation_;
		scale = scale_;
	}

	void RenderGui() override;
};