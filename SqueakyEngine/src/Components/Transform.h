#pragma once
#include "Component.h"
#include <glm/matrix.hpp>
#include <glm/ext.hpp>
#include "Component.h"
class Transform : public Component {
private:
	friend class PhysicsBody;
	glm::vec3 pos{};
	glm::vec3 lastPos{};
	glm::vec3 scale{};

	glm::quat rotation{};
public:
	//Transform();
	explicit Transform(glm::vec3 pos_=glm::vec3(0), glm::quat orientation_ = glm::quat(0, 0, 0,0), glm::vec3 scale_ = glm::vec3(1.0f, 1.0f, 1.0f));
	~Transform() override;
	bool OnCreate() override;
	void OnDestroy() override;
	void Update(const float deltaTime) override;
	inline glm::mat4 TranslateMatrix() const;

	void Render() const;

	inline glm::vec3 GetPosition() const { return pos; }
	 glm::vec3 GetWorldPosition() const;
	inline glm::vec3 GetScale() const { return scale; }
	inline glm::quat GetRotation() const { return (rotation); }
	inline glm::vec3 GetRotationEuler() const {
		return glm::eulerAngles(rotation);
	}
	inline void const SetPosition(const glm::vec3& pos_) { lastPos = pos; pos = pos_; }
	inline void const SetScale(const glm::vec3& scale_)  {  scale=scale_; }
	inline void const SetRotation(const glm::quat &rotation_)  { rotation = (rotation_); }
	//inline void const SetRotationEuler(const glm::vec3& rotation_)  {
	//	rotation =  rotation_;
	//}
	inline glm::vec3 GetForward()const { return glm::inverse(GetTransformMatrix())[2]; }
	inline glm::vec3 GetRight()const { return glm::inverse(GetTransformMatrix())[0]; }
	inline glm::vec3 GetUp() const { return glm::inverse(GetTransformMatrix())[1]; }
	glm::mat4 GetTransformMatrix(bool local=true) const;

	glm::vec3 GetDelta() const { return pos - lastPos; }
	
	inline void SetTransform(glm::vec3 pos_, glm::vec3 orientation_, glm::vec3 scale_ = glm::vec3(1.0f, 1.0f, 1.0f)) {
		pos = pos_;
		rotation = orientation_;// glm::quat(orientation_);
		//eulerAngles = orientation_;
		scale = scale_;
	}

	void RenderGui() override;
	//
};