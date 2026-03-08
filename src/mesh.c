#include "mesh.h"
#include "graphics.h"
#include "shaders.h"
#include <stdlib.h>

#define QUAD_VERTICES_SIZE 4
#define QUAD_INDICES_SIZE 6

void set_quad_vertices(vertex_t* vertices, unsigned int* indices)
{
	vertices[0].position = (vec2_t) {1.0, 0.0};
	vertices[0].uv = (uv_t) {1.0, 0.0};
	vertices[0].color = (color_t) {1, 1, 1, 1};

	vertices[1].position = (vec2_t) {0.0, 1.0};
	vertices[1].uv = (uv_t) {0.0, 1.0};
	vertices[1].color = (color_t) {1, 1, 1, 1};

	vertices[2].position.x = 0.0; vertices[2].position.y = 0.0;
	vertices[2].uv.x = 0.0; vertices[2].uv.y = 0.0;
	vertices[2].color = (color_t) {1, 1, 1, 1};

	vertices[3].position.x = 1.0; vertices[3].position.y = 1.0;
	vertices[3].uv.x = 1.0; vertices[3].uv.y = 1.0;
	vertices[3].color = (color_t) {1, 1, 1, 1};

	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 0; indices[4] = 3; indices[5] = 1;
}

mesh_t* create_mesh_quad()
{
	mesh_t* mesh = malloc(sizeof(mesh_t));

	mesh->indices_amount = QUAD_INDICES_SIZE;
	mesh->vertices_amount = QUAD_VERTICES_SIZE;

	vertex_t vertices[QUAD_VERTICES_SIZE];
	unsigned int indices[QUAD_INDICES_SIZE];

	set_quad_vertices(vertices, indices);

	glGenVertexArrays(1, &mesh->vao);
	glGenBuffers(1, &mesh->vbo);
	glGenBuffers(1, &mesh->ebo);

	glBindVertexArray(mesh->vao);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);

	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(vertex_t) * QUAD_VERTICES_SIZE,
		vertices,
		GL_STATIC_DRAW
	);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);

	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		sizeof(unsigned int) * QUAD_INDICES_SIZE,
		indices,
		GL_STATIC_DRAW
	);

	glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
	glEnableVertexAttribArray(VERTEX_ATTR_COLOR);
	glEnableVertexAttribArray(VERTEX_ATTR_UV);

	glVertexAttribPointer(
		VERTEX_ATTR_POSITION,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(vertex_t),
		(void*)offsetof(vertex_t, position)
	);

	glVertexAttribPointer(
		VERTEX_ATTR_COLOR,
		4,
		GL_UNSIGNED_INT,
		GL_FALSE,
		sizeof(vertex_t),
		(void*)offsetof(vertex_t, color)
	);

	glVertexAttribPointer(
		VERTEX_ATTR_UV,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(vertex_t),
		(void*)offsetof(vertex_t, uv)
	);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return mesh;
}

