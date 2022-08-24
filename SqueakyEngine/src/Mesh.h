#pragma once
#include <glad/glad.h>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include "Component.h"
class Mesh : public Component {
private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvCoords;
	size_t dataLength;
	GLenum drawmode;

	GLuint vao, vbo;
public:
	Mesh(Component* parent_,  const char* filename_);

	~Mesh();
	void StoreMeshData(GLenum drawmode_);

	bool OnCreate();
	void OnDestroy();
	void Update(const float deltaTime);
	void Render() const;
	//bool OnCreate();
	//void OnDestroy();
	//void Update(const float deltaTime);
	//void Render() const;
	//void Render(GLenum drawmode) const;

};

