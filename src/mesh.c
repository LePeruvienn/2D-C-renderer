#include "mesh.h"
#include "graphics.h"
#include "shaders.h"
#include <stdlib.h>

#define QUAD_VERTICES_SIZE 4
#define QUAD_INDICES_SIZE 6

void set_quad_vertices(vertexUV_t* vertices, unsigned int* indices)
{
	vertices[0].position.x = 1.0; vertices[0].position.y = 0.0;
	vertices[0].texture.x = 1.0; vertices[0].texture.y = 1.0;

	vertices[1].position.x = 0.0; vertices[1].position.y = 1.0;
	vertices[1].texture.x = 0.0; vertices[1].texture.y = 0.0;


	vertices[2].position.x = 0.0; vertices[2].position.y = 0.0;
	vertices[2].texture.x = 0.0; vertices[2].texture.y = 1.0;

	vertices[3].position.x = 1.0; vertices[3].position.y = 1.0;
	vertices[3].texture.x = 1.0; vertices[3].texture.y = 0.0;

	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 0; indices[4] = 3; indices[5] = 1;
}

mesh_t* create_mesh_quad()
{
	mesh_t* mesh = malloc(sizeof(mesh_t));

	vertexUV_t vertices[QUAD_VERTICES_SIZE];
	unsigned int indices[QUAD_INDICES_SIZE];

	set_quad_vertices(vertices, indices);

	glGenVertexArrays(1, &mesh->vao);
	glGenBuffers(1, &mesh->vbo);
	glGenBuffers(1, &mesh->ebo);

	glBindVertexArray(mesh->vao);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);

	glBufferData(
		mesh->vbo,
		sizeof(vertexUV_t) * QUAD_VERTICES_SIZE,
		vertices,
		GL_STATIC_DRAW
	);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->vbo);

	glBufferData(
		mesh->ebo,
		sizeof(unsigned int) * QUAD_INDICES_SIZE,
		indices,
		GL_STATIC_DRAW
	);

	glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);
	glEnableVertexAttribArray(VERTEX_ATTR_POSITION);

	// TODO VERTEX ATTRIB DATA !!!

	glBindVertexArray(0);

	return mesh;
}

void free_mesh(mesh_t* mesh)
{

}
