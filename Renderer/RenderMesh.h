#pragma once
#include <glad/glad.h>
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include <string>
#include <vector>

class RenderMesh
{
private:
	std::string fileName;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvCoords;
	std::vector<glm::vec3> colors;
	size_t dataLength;
	GLenum drawmode;

	GLuint vao, vbo;
public:
	explicit RenderMesh(const std::string& filename = "src/Meshes/cube.obj");
	std::string GetFileName()const;
	~RenderMesh();
	void StoreMeshData(GLenum drawmode_);
	void LoadModel(const std::string& filename);
	void Render() const;
	size_t GetSize() { return dataLength; }
	GLuint GetVAO() { return vao; }
};
