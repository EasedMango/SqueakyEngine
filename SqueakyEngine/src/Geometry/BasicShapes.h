#pragma once
#include <glm/matrix.hpp>
#include <vector>
#include <glad/glad.h>
static const std::vector<glm::vec3 >Triangle2DVert= {
glm::vec3(-0.0f, -0.0f, 0.0f),
glm::vec3(1.0f, -0.0f, 0.0f),
glm::vec3(0.0f,  1.0f, 0.0f),
};
static const std::vector<glm::vec3 >Square2DVert = {
glm::vec3(-1.0f, -1.0f, 0.0f),
glm::vec3(-1.0f, 1.0f, 0.0f),
glm::vec3(1.0f, 1.0f, 0.0f),
glm::vec3(-1.0f, -1.0f, 0.0f),
glm::vec3(1.0f, 1.0f, 0.0f),
glm::vec3(1.0f, -1.0f, 0.0f)


};
class BasicShapes
{
private:
	std::vector<glm::vec4> vertices;
public:

	std::vector<glm::vec4> GetVertices() const { return vertices; }
	void SetVertices(const std::vector<glm::vec4>& verts) { vertices = verts; }
	bool OnCreate();
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