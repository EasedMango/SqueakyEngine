#include "RenderMesh.h"
#include <iostream>
#include <filesystem>
#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
// Optional. define TINYOBJLOADER_USE_MAPBOX_EARCUT gives robust trinagulation. Requires C++11
//#define TINYOBJLOADER_USE_MAPBOX_EARCUT
#include "tiny_obj_loader.h"


RenderMesh::RenderMesh(const std::string& filename) : fileName(filename)
{
    if (vertices.size() == 0)
    {
        LoadModel(filename);
    }
    StoreMeshData(GL_TRIANGLES);
}

RenderMesh::~RenderMesh()
= default;

void RenderMesh::StoreMeshData(GLenum drawmode_)
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
    glGenBuffers(1, &vbo); // gens 1 
    glBindBuffer(GL_ARRAY_BUFFER, vbo); // make active object 
    std::cout << VERTEX_LENGTH + NORMAL_LENGTH + TEXCOORD_LENGTH + COLORS_LENGTH << " ~~~~~~~~~~~~~\n";
    glBufferData(GL_ARRAY_BUFFER, VERTEX_LENGTH + NORMAL_LENGTH + TEXCOORD_LENGTH + COLORS_LENGTH, nullptr,
        GL_STATIC_DRAW); //give data
    /// assigns the addr of "points" to be the beginning of the array buffer "sizeof(points)" in length
    glBufferSubData(GL_ARRAY_BUFFER, 0, VERTEX_LENGTH, &vertices[0]);
    glEnableVertexAttribArray(verticiesLayoutLocation);
    glVertexAttribPointer(verticiesLayoutLocation, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(0));
    /// assigns the addr of "normals" to be "sizeof(points)" offset from the beginning and "sizeof(normals)" in length 
    if (!normals.empty())
    {
        glBufferSubData(GL_ARRAY_BUFFER, VERTEX_LENGTH, NORMAL_LENGTH, &normals[0]);
        glEnableVertexAttribArray(normalsLayoutLocation);
        glVertexAttribPointer(normalsLayoutLocation, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(VERTEX_LENGTH));
    }
    if (!uvCoords.empty())
    {
        /// assigns the addr of "texCoords" to be "sizeof(points) + sizeof(normals)" offset from the beginning and "sizeof(texCoords)" in length  
        glBufferSubData(GL_ARRAY_BUFFER, VERTEX_LENGTH + NORMAL_LENGTH, TEXCOORD_LENGTH, &uvCoords[0]);
        glEnableVertexAttribArray(uvCoordsLayoutLocation);
        glVertexAttribPointer(uvCoordsLayoutLocation, 2, GL_FLOAT, GL_FALSE, 0,
            reinterpret_cast<void*>(VERTEX_LENGTH + NORMAL_LENGTH));
    }
    if (!colors.empty())
    {
        /// assigns the addr of "texCoords" to be "sizeof(points) + sizeof(normals)" offset from the beginning and "sizeof(texCoords)" in length  
        glBufferSubData(GL_ARRAY_BUFFER, VERTEX_LENGTH + NORMAL_LENGTH + TEXCOORD_LENGTH, COLORS_LENGTH, &colors[0]);
        glEnableVertexAttribArray(colorsLayoutLocation);
        glVertexAttribPointer(colorsLayoutLocation, 3, GL_FLOAT, GL_FALSE, 0,
            reinterpret_cast<void*>(VERTEX_LENGTH + NORMAL_LENGTH + TEXCOORD_LENGTH));
    }


    dataLength = vertices.size();
  //  vertices.clear();
   // normals.clear();
   // uvCoords.clear();
#undef VERTEX_LENGTH
#undef NORMAL_LENGTH
#undef TEXCOORD_LENGTH
}

void RenderMesh::LoadModel(const std::string& filename)
{
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;
    
    vertices.clear();
    normals.clear();
    uvCoords.clear();
    const char* fn = filename.c_str();
    if (!LoadObj(&attrib, &shapes, &materials, &warn, &err, fn))
    {
        throw std::runtime_error(warn + err);
    }
    for (const auto& shape : shapes)
    {
        for (const auto& index : shape.mesh.indices)
        {
            glm::vec3 vertex{};
            vertex.x = attrib.vertices[3 * index.vertex_index + 0];
            vertex.y = attrib.vertices[3 * index.vertex_index + 1];
            vertex.z = attrib.vertices[3 * index.vertex_index + 2];
            glm::vec3 normal{};
            if (!attrib.normals.empty())
            {
                normal.x = attrib.normals[3 * index.normal_index + 0];
                normal.y = attrib.normals[3 * index.normal_index + 1];
                normal.z = attrib.normals[3 * index.normal_index + 2];
            }
            glm::vec2 uvCoord{};
            if (!attrib.texcoords.empty())
            {
                uvCoord.x = attrib.texcoords[2 * index.texcoord_index + 0];
                uvCoord.y = attrib.texcoords[2 * index.texcoord_index + 1];
            }
            // Optional: vertex colors
            glm::vec3 color(0);
            if (!attrib.colors.empty())
            {
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
    std::cout << std::filesystem::current_path() << filename << std::endl;
}
void RenderMesh::Render() const
{
    glBindVertexArray(vao);

    glDrawArrays(GL_TRIANGLES, 0, dataLength);
    glBindVertexArray(0); // Unbind the VAO
}

std::string RenderMesh::GetFileName() const
{ return fileName; }
