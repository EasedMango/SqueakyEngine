#include "Mesh.h"
#include <glm/ext.hpp>
#include "Logger.h"
#include <iostream>
#include <filesystem>

#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
// Optional. define TINYOBJLOADER_USE_MAPBOX_EARCUT gives robust trinagulation. Requires C++11
//#define TINYOBJLOADER_USE_MAPBOX_EARCUT
#include "tiny_obj_loader.h"
Mesh::Mesh(const char* filename_) :
	Component(nullptr), filename(filename_)
{
	//upload the vertex data to the gpu
	LoadModel(filename);

}

Mesh::Mesh(std::vector<glm::vec3> verts) :
	Component(nullptr), vertices(verts)
{

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
#define COLORS_LENGTH (colors.size() * (sizeof(glm::vec2)))
	const int verticiesLayoutLocation = 0;
	const int normalsLayoutLocation = 1;
	const int uvCoordsLayoutLocation = 2;
	const int colorsLayoutLocation = 3;
	/// create and bind the VOA
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	/// Create and initialize vertex buffer object VBO
	glGenBuffers(1, &vbo);// gens 1 
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // make active object 
	std::cout << VERTEX_LENGTH + NORMAL_LENGTH + TEXCOORD_LENGTH + COLORS_LENGTH << " ~~~~~~~~~~~~~\n";
	glBufferData(GL_ARRAY_BUFFER, VERTEX_LENGTH + NORMAL_LENGTH + TEXCOORD_LENGTH + COLORS_LENGTH, 0, GL_STATIC_DRAW); //give data
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
	if (colors.size() != 0) {

		/// assigns the addr of "texCoords" to be "sizeof(points) + sizeof(normals)" offset from the beginning and "sizeof(texCoords)" in length  
		glBufferSubData(GL_ARRAY_BUFFER, VERTEX_LENGTH + NORMAL_LENGTH + TEXCOORD_LENGTH, COLORS_LENGTH, &colors[0]);
		glEnableVertexAttribArray(colorsLayoutLocation);
		glVertexAttribPointer(colorsLayoutLocation, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(VERTEX_LENGTH + NORMAL_LENGTH + TEXCOORD_LENGTH));

	}






	dataLength = vertices.size();
	vertices.clear();
	normals.clear();
	uvCoords.clear();
#undef VERTEX_LENGTH
#undef NORMAL_LENGTH
#undef TEXCOORD_LENGTH
}

void Mesh::LoadModel(const char* filename)
{
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn, err;

	vertices.clear();
	normals.clear();
	uvCoords.clear();
	Logger::Info("FileName:");
	std::cout << std::filesystem::current_path() << " " << filename<< std::endl;
	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename)) {
		throw std::runtime_error(warn + err);
	}

	//int shapeCount = shapes.size();
	//


	//	for (int i = 0; i < shapeCount; ++i) {
	//		int indicesCount = shapes[i].mesh.indices.size();
	//		
	//		for (int j = 0; j < indicesCount;++j) {
	//			shapes[i].mesh.indices[j].vertex_index;
	//		}
	//	}

	for (const auto& shape : shapes) {
		for (const auto& index : shape.mesh.indices) {
			glm::vec3 vertex{};
			vertex.x = attrib.vertices[3 * index.vertex_index + 0];
			vertex.y = attrib.vertices[3 * index.vertex_index + 1];
			vertex.z = attrib.vertices[3 * index.vertex_index + 2];
			glm::vec3 normal{};
			if (attrib.normals.size() != 0) {

				normal.x = attrib.normals[3 * index.normal_index + 0];
				normal.y = attrib.normals[3 * index.normal_index + 1];
				normal.z = attrib.normals[3 * index.normal_index + 2];
			}
			glm::vec2 uvCoord{};
			if (attrib.texcoords.size() != 0) {

				uvCoord.x = attrib.texcoords[2 * index.texcoord_index + 0];
				uvCoord.y = attrib.texcoords[2 * index.texcoord_index + 1];
			}
			// Optional: vertex colors
			glm::vec3 color(0);
			if (attrib.colors.size() != 0) {
				color.x = attrib.colors[3 * index.vertex_index + 0];
				color.y = attrib.colors[3 * index.vertex_index + 1];
				color.z = attrib.colors[3 * index.vertex_index + 2];
			}
			vertices.push_back(vertex);
			normals.push_back(normal);
			uvCoords.push_back(uvCoord);
			colors.push_back(color);
		}
	}
}

bool Mesh::OnCreateVert() {
	if (isCreated) return true;
	StoreMeshData(GL_TRIANGLES);
	isCreated = true;
	return true;

}

bool Mesh::OnCreate()
{

	if (isCreated) return true;
	if (vertices.size() == 0) {
		LoadModel(filename);
	}
	StoreMeshData(GL_TRIANGLES);
	isCreated = true;
	return true;
}


void Mesh::Render() const {
	glBindVertexArray(vao);

	glDrawArrays(GL_TRIANGLES, 0, dataLength);
	glBindVertexArray(0); // Unbind the VAO
}

void Mesh::RenderGui()
{
}



void Mesh::OnDestroy() {
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}

/// Currently unused.

void Mesh::Update(const float deltaTime) {}