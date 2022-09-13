#pragma once
#include <glad/glad.h>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include "Component.h"
class Mesh : public Component {
private:
	const char* filename;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvCoords;
	std::vector<glm::vec3> colors;
	size_t dataLength;
	GLenum drawmode;

	GLuint vao, vbo;
public:
	Mesh(const char* filename_="src/Meshes/cube.obj");
	Mesh( std::vector<glm::vec3> verts);
	~Mesh();
	void StoreMeshData(GLenum drawmode_);
	void LoadModel(const char* filename);

	bool OnCreate();
	bool OnCreateVert();
	void OnDestroy();
	void Update(const float deltaTime);
	void Render() const;
	void RenderGui() override;
	//void OnDestroy();
	//void Update(const float deltaTime);
	//void Render() const;
	//void Render(GLenum drawmode) const;

};

