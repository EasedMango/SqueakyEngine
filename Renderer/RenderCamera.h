#pragma once
#include <glm/matrix.hpp>
#include <memory>
enum CameraType { Perspective, Orthographic };
class RenderCamera
{

private:
	CameraType type;
	float fov;
	glm::mat4  projectionMatrix;
	glm::mat4  viewMatrix;
	unsigned int uboMatriciesID;
	unsigned int bindingPoint;
public:
	RenderCamera(const float& fov_);

	virtual ~RenderCamera();

	virtual void OnDestroy();

	void SendUniforms(class RenderShader* shader) const;

	glm::mat4 GetProjectionMatrix() const;

	glm::mat4 GetViewMatrix()const;

	void SetProjectionMatrix(const glm::mat4 & proj)
	{
		projectionMatrix = proj;
	}
	void SetViewMatrix(const glm::mat4& view)
	{
		viewMatrix = view;
	}

	unsigned int GetMatriciesID() const { return uboMatriciesID; }

	void UpdateProjectionMatrix( const float& aspectRatio, const float& near, const float& far);
	virtual void UpdateViewMatrix();
};