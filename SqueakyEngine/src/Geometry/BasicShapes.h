#pragma once
#include <glm/matrix.hpp>
#include <vector>
#include <glad/glad.h>
class BasicShapes
{
private:
	glm::mat4 modelMatrix;
	std::vector<glm::vec4> vertices;

	GLuint vao;
	GLuint vbo;
	GLint mvp_location;
	GLint vpos_location;
	GLint vcol_location;
public:
	glm::mat4 GetModelMatrix() const { return modelMatrix; }
	void SetModelMatrix(const glm::mat4& mm) { modelMatrix = (mm); }
	std::vector<glm::vec4> GetVertices() const { return vertices; }
	void SetVertices(const std::vector<glm::vec4>& verts) { vertices = verts; }
	bool OnCreate();
	GLuint GetMvp()const { return mvp_location; }
	void Render();

};
static const glm::vec3 g_vertex_buffer_data[] = {
   glm::vec3( - 1.0f, -1.0f, 0.0f),
   glm::vec3(1.0f, -1.0f, 0.0f),
   glm::vec3(0.0f,  1.0f, 0.0f),
};
struct Triangle : public BasicShapes
{

	Triangle();



};