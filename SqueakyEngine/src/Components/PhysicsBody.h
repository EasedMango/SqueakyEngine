#pragma once
#include "Transform.h"
#include "Component.h"
#include <glm/vec3.hpp>
#include <string>
#include <vector>
#include "Collider.h"


class PhysicsBody : public Component
{
private:

	//Collider* collider;


	bool isStatic;
	bool collision;
	float mass, rotationalInertia{};
	glm::vec3 velocity{}, acceleration, prevAccel;

	glm::vec3 penatrationDepth{};

	std::vector <glm::vec3> forces;

	float angle{}, angularVelocity{}, angularAcceleration{};

	glm::vec3  rotationVelocity, rotationAcceleration;
	
	std::vector <glm::vec3> rotationalForces;

	glm::vec3 scale{};

	float length, width, height;
	float radius;


protected:
	Transform* transform;
public:
	inline void ApplyForce(glm::vec3 force) { acceleration = (force / mass); };
	PhysicsBody(bool isStatic_ = false,float mass_=1, glm::vec3 vel = glm::vec3(0));
	Transform* GetTransform()const { return transform; }
	void Update(const float deltaTime) override;
	bool OnCreate() override;
	void OnDestroy() override;
	void Render() const override;
	void RenderGui() override;
	float GetRotationalInertia() const { return rotationalInertia; }

	Collider* GetCollider() const;

	template<class  T>
	T* GetShape()
	{
		if (const Collider* collide = GetCollider(); std::holds_alternative<T*>(collide->GetShape()))
		{
			return  std::get<T*>(collide->GetShape());
		}
		return nullptr;
	}





	void  AddForce(const glm::vec3 force) { forces.push_back(force); }

	//Collision Data
	float GetLength() const { return mass; }
	void  SetLength(float length_) { length = length_; }
	float GetWidth() const { return width; }
	void  SetWidth(float width_) { width = width_; }
	float GetHeight() const { return height; }
	void  SetHeight(float height_) { height = height_; }
	float GetRadius() const { return radius; }
	void  SetRadius(float radius_) { radius = radius_; }

	bool GetIsStatic()const { return isStatic; }

	//Rotation Data
	float GetAngle() const { return angle; }
	void  SetAngle(float angle_) { angle = angle_; }
	float GetAngularVelocity() const { return angularVelocity; }
	void  SetAngularVelocity(float angleVel_) { angularVelocity = angleVel_; }
	float GetAngularAcceleration() const { return angularAcceleration; }
	void  SetAngularAcceleration(float angleAccel_) { angularAcceleration = angleAccel_; }


	//Physics Properties
	float GetMass() const { return mass; }
	void SetMass(float mass_) { mass = mass_; }
	glm::vec3 GetPos() const { return transform->pos; }
	void SetPos(glm::vec3 pos_) { transform->lastPos = transform->pos; transform->pos = pos_; }
	glm::vec3 GetVel() const { return velocity; }
	void SetVel(glm::vec3 vel_) { velocity = vel_; }
	glm::vec3 GetAccel() const { return acceleration; }
	void  SetAccel(glm::vec3 accel_) { acceleration = accel_; }
	glm::vec3 GetPrevAccel() const { return prevAccel; }
	void  SetPrevAccel(glm::vec3 prevAccel_) { prevAccel = prevAccel_; }

	glm::vec3 GetDepthPen() const { return penatrationDepth; }
	void const SetDepthPen(glm::vec3 depthPen) { penatrationDepth = depthPen; }
	glm::quat GetRotation() const { return (transform->rotation); }
	void  SetRotation(glm::quat angle_) const { transform->rotation = angle_; }
	glm::vec3 GetRotVel() const { return rotationVelocity; }
	void  SetRotVel(glm::vec3 vel_) { rotationVelocity = vel_; }
	glm::vec3 GetRotAccel() const { return rotationAcceleration; }
	void  SetRotAccel(glm::vec3 accel_) { rotationAcceleration = accel_; }

	glm::vec3 GetScale() const { return scale; }
	void SetScale(glm::vec3 scale_) { scale = scale_; }

	void const Print();
	//Object Name





};

