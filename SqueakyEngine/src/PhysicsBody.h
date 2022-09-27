#pragma once
#include "Transform.h"
#include "Component.h"
#include <glm/vec3.hpp>
#include <string>
#include <vector>


class PhysicsBody : public Component
{
private:
	Transform* transform;
	bool isStatic;
	float mass, rotationalInertia;
	glm::vec3 velocity, acceleration, prevAccel;


	std::vector <glm::vec3> forces;

	float angle, angularVelocity, angularAcceleration;

	glm::vec3  rotationVelocity, rotationAcceleration;

	glm::vec3 scale;

	float length, width, height;
	float radius;

	
	inline void ApplyForce(glm::vec3 force) { acceleration = (force / mass); };

public:

	PhysicsBody(float mass_=1, glm::vec3 vel = glm::vec3(0),bool isStatic_ = false);

	void Update(const float deltaTime);
	bool OnCreate() override;
	void OnDestroy() override;
	void Render() const override;
	void RenderGui() override;

	

	void const AddForce(glm::vec3 force) { forces.push_back(force); }

	//Collision Data
	float GetLength() const { return mass; }
	void const SetLength(float length_) { length = length_; }
	float GetWidth() const { return width; }
	void const SetWidth(float width_) { width = width_; }
	float GetHeight() const { return height; }
	void const SetHeight(float height_) { height = height_; }
	float GetRadius() const { return radius; }
	void const SetRadius(float radius_) { radius = radius_; }

	bool GetIsStatic()const { return isStatic; }

	//Rotation Data
	float GetAngle() const { return angle; }
	void const SetAngle(float angle_) { angle = angle_; }
	float GetAngularVelocity() const { return angularVelocity; }
	void const SetAngularVelocity(float angleVel_) { angularVelocity = angleVel_; }
	float GetAngularAcceleration() const { return angularAcceleration; }
	void const SetAngularAcceleration(float angleAccel_) { angularAcceleration = angleAccel_; }


	//Physics Properties
	float GetMass() const { return mass; }
	void const SetMass(float mass_) { mass = mass_; }
	glm::vec3 GetPos()  { return transform->pos; }
	void const SetPos(glm::vec3 pos_) { transform->pos = pos_; }
	glm::vec3 GetVel() const { return velocity; }
	void const SetVel(glm::vec3 vel_) { velocity = vel_; }
	glm::vec3 GetAccel() const { return acceleration; }
	void const SetAccel(glm::vec3 accel_) { acceleration = accel_; }
	glm::vec3 GetPrevAccel() const { return prevAccel; }
	void const SetPrevAccel(glm::vec3 prevAccel_) { prevAccel = prevAccel_; }

	glm::vec3 GetRotation() const { return transform->rotation; }
	void const SetRotation(glm::vec3 angle_) { transform->rotation = angle_; }
	glm::vec3 GetRotVel() const { return rotationVelocity; }
	void const SetRotVel(glm::vec3 vel_) { rotationVelocity = vel_; }
	glm::vec3 GetRotAccel() const { return rotationAcceleration; }
	void const SetRotAccel(glm::vec3 accel_) { rotationAcceleration = accel_; }

	glm::vec3 GetScale() const { return scale; }
	void const SetScale(glm::vec3 scale_) { scale = scale_; }

	void const Print();
	//Object Name





};

