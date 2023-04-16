#include "RenderCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Renderer.h"
#include "RenderShader.h"
#include "UBO_Padding.h"

RenderCamera::RenderCamera(const float& fov_): type(Perspective), fov(fov_), projectionMatrix(1), viewMatrix(1), uboMatriciesID(0), bindingPoint(0)
{

}
bool RenderCamera::OnCreate()
{
    size_t buffer_size = 2 * UBO_PADDING::MAT4;
    glGenBuffers(1, &uboMatriciesID);
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatriciesID);
    glBufferData(GL_UNIFORM_BUFFER, buffer_size, nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, uboMatriciesID);
    return true;
}


RenderCamera::~RenderCamera()
= default;

void RenderCamera::OnDestroy()
{
    glDeleteBuffers(1, &uboMatriciesID);
}

void RenderCamera::SendUniforms(RenderShader* shader) const
{
    //glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, value_ptr(GetProjectionMatrix()));
    //glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, value_ptr(GetViewMatrix()));
    glBindBuffer(GL_UNIFORM_BUFFER, GetMatriciesID());
}

glm::mat4 RenderCamera::GetProjectionMatrix() const
{ return projectionMatrix; }

glm::mat4 RenderCamera::GetViewMatrix() const
{ return viewMatrix; }

void RenderCamera::UpdateProjectionMatrix( const float& aspectRatio, const float& near, const float& far)
{
    projectionMatrix = glm::perspective(fov, aspectRatio, near, far);

    size_t offset = 0;
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatriciesID);
    glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(glm::mat4), glm::value_ptr( projectionMatrix));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void RenderCamera::UpdateViewMatrix()
{
    size_t offset = sizeof(glm::mat4);
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatriciesID);
    glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(glm::mat4), glm::value_ptr(viewMatrix));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
