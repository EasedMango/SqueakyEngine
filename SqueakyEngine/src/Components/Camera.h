#pragma once
#include <glm/matrix.hpp>
#include "Component.h"
#include "Actor.h"

enum CameraType { Prespective, Orthographic };
class Camera : public Component
{
private:
	CameraType type;
	float fov;
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
	class Transform* camTrn;


public:
	Camera(float fov_);


	/**
	 * \brief Perspective Camera Constructor 
	 */
	//Camera(const int& fov);
	/**
	 * \brief Orthographic Camera Constructor
	 */
	//Camera(const int& fov);

	void UpdateViewMatrix();




	 bool OnCreate() override;


	 void OnDestroy() override;


	 void Update(const float deltaTime) override;


	 void Render() const override;


	 void RenderGui() override;

	glm::mat4 GetProjectionMatrix() const { return projectionMatrix; }
	//glm::vec3 Get
	glm::mat4 GetViewMatrix() const;

};

