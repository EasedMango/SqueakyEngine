#include "Mesh.h"
#include <glm/ext.hpp>
#include <iostream>
Mesh::Mesh(Component* parent_, std::vector<glm::vec3>& verts) : vertices(verts),
Component(parent_)
{
	//upload the vertex data to the gpu
	glGenBuffers(1, &vbo);// gens 1 buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // make active object 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices.data()[0], GL_STATIC_DRAW);//copy vertex data to that object
}

Mesh::~Mesh()
{
}

void Mesh::StoreMeshData(GLenum drawmode_)
{
	drawmode = drawmode_;
#define VERTEX_LENGTH 	(vertices.size() * (sizeof(glm::vec3)))
#define NORMAL_LENGTH 	(normals.size() * (sizeof(glm::vec3)))
#define TEXCOORD_LENGTH (uvCoords.size() * (sizeof(glm::vec2)))
	const int verticiesLayoutLocation = 0;
	const int normalsLayoutLocation = 1;
	const int uvCoordsLayoutLocation = 2;
	/// create and bind the VOA
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	/// Create and initialize vertex buffer object VBO
	glGenBuffers(1, &vbo);// gens 1 buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // make active object 
	glBufferData(GL_ARRAY_BUFFER, VERTEX_LENGTH + NORMAL_LENGTH + TEXCOORD_LENGTH, nullptr, GL_STATIC_DRAW); //give data
	/// assigns the addr of "points" to be the beginning of the array buffer "sizeof(points)" in length
	glBufferSubData(GL_ARRAY_BUFFER, 0, VERTEX_LENGTH, &vertices[0]);
	glEnableVertexAttribArray(verticiesLayoutLocation);
	glVertexAttribPointer(verticiesLayoutLocation, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(0));
	/// assigns the addr of "normals" to be "sizeof(points)" offset from the beginning and "sizeof(normals)" in length 
	if (normals.size() != 0) {
		glBufferSubData(GL_ARRAY_BUFFER, VERTEX_LENGTH, NORMAL_LENGTH, &normals[0]);
		glEnableVertexAttribArray(normalsLayoutLocation);
		glVertexAttribPointer(normalsLayoutLocation, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(VERTEX_LENGTH));
	}
	if (uvCoords.size() != 0) {
		/// assigns the addr of "texCoords" to be "sizeof(points) + sizeof(normals)" offset from the beginning and "sizeof(texCoords)" in length  
		glBufferSubData(GL_ARRAY_BUFFER, VERTEX_LENGTH + NORMAL_LENGTH, TEXCOORD_LENGTH, &uvCoords[0]);
		glEnableVertexAttribArray(uvCoordsLayoutLocation);
		glVertexAttribPointer(uvCoordsLayoutLocation, 2, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(VERTEX_LENGTH + NORMAL_LENGTH));
	}


	


	

	dataLength = vertices.size();
	vertices.clear();
	normals.clear();
	uvCoords.clear();
#undef VERTEX_LENGTH
#undef NORMAL_LENGTH
#undef TEXCOORD_LENGTH
}

bool Mesh::OnCreate() {
	if (isCreated) return true;
	StoreMeshData(GL_TRIANGLES);
	isCreated = true;
	return true;
}


void Mesh::Render() const {
	glBindVertexArray(vao);

	glDrawArrays(GL_TRIANGLES, 0, dataLength);
	glBindVertexArray(0); // Unbind the VAO
}



void Mesh::OnDestroy() {
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}

/// Currently unused.

void Mesh::Update(const float deltaTime) {}