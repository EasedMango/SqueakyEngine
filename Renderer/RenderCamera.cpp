#include "RenderCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Renderer.h"
#include "RenderShader.h"

RenderCamera::RenderCamera(const glm::mat4 viewMatrix, const glm::mat4 projectionMatrix): projectionMatrix(projectionMatrix), viewMatrix(viewMatrix)
{
}

RenderCamera::~RenderCamera()
{
}

void RenderCamera::SendUniforms(RenderShader* shader) const
{
    glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, value_ptr(GetProjectionMatrix()));

    glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, value_ptr(GetViewMatrix()));
}

glm::mat4 RenderCamera::GetProjectionMatrix() const
{ return projectionMatrix; }

glm::mat4 RenderCamera::GetViewMatrix() const
{ return viewMatrix; }
