#pragma once
#include <glm/matrix.hpp>

    class RenderCamera
    {

    private:
        glm::mat4 projectionMatrix;
        glm::mat4 viewMatrix;
    public:
        RenderCamera(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
        ~RenderCamera();

        void SendUniforms(class RenderShader* shader) const;

         glm::mat4 GetProjectionMatrix() const;
         glm::mat4 GetViewMatrix()const;
         void UpdateViewMatrix(const glm::mat4& view)
         {
             viewMatrix = view;
         }
    };