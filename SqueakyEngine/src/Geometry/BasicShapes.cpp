#include "BasicShapes.h"

Triangle::Triangle()
{
	SetVertices(std::vector < glm::vec4 > {
		{glm::vec4(-0.6f, -0.4f, 0.f, 0.f)},
		{ glm::vec4(0.6f, -0.4f, 0.f, 0.f) },
		{ glm::vec4(0.f, 0.6f, 0.f, 0.f) }
	});

	
}

bool BasicShapes::OnCreate()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	// This will identify our vertex buffer
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vbo);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	return true;
}

void BasicShapes::Render() {
	/* Render here */
			//glClear(GL_COLOR_BUFFER_BIT);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(0);
}

