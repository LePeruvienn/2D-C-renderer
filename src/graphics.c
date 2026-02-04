#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include "graphics.h"

// globals
const GLuint VERTEX_ATTR_POSITION = 0;
const GLuint VERTEX_ATTR_COLOR = 1;

// locals
static const uint64_t DEFAULT_VERTICES_SIZE = 100;

static GLuint vbo;
static GLuint vao;

static vertex_t** vertices;
static uint64_t vertices_amount = 0;
static uint64_t vertices_size = 0;

int add_vertex(vertex_t* vertex)
{
	if (vertices_amount == vertices_size)
		return 1;

	vertices[vertices_amount] = vertex;
	vertices_amount++;

	return 0;
}

int add_vertices(vertex_t** ivertices, uint64_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		if (add_vertex(ivertices[i]) != 0)
			return 1;
	}
	
	return 0;
}

vertex_t* create_vertex(vec2_t* position, color_t* color)
{
	vertex_t* vertex = malloc(sizeof(vertex_t));
	vertex->position = *position;
	vertex->color = *color;

	return vertex;
}

void draw_triangle()
{
	vertex_t* vertices[] = {
		create_vertex(create_vec2(0.0, 1.0), create_color(1.0, 1.0, 1.0)),
		create_vertex(create_vec2(1.0, 0.0), create_color(1.0, 1.0, 1.0)),
		create_vertex(create_vec2(-1.0, 0.0), create_color(1.0, 1.0, 1.0))
	};

	add_vertices(vertices, 3);
}

void init_graphics()
{
	vertices = malloc(sizeof(vertex_t*) * DEFAULT_VERTICES_SIZE);
	vertices_size += DEFAULT_VERTICES_SIZE;

	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	draw_triangle();

	glBufferData(
		GL_ARRAY_BUFFER,
		vertices_amount * sizeof(vertex_t),
		vertices,
		GL_STATIC_DRAW);
	
	glBindBuffer (GL_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);

	glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
	glEnableVertexAttribArray(VERTEX_ATTR_COLOR);


	glVertexAttribPointer(
		VERTEX_ATTR_POSITION,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(vertex_t),
		(const GLvoid*) (offsetof(vertex_t, position))
	);

	glVertexAttribPointer(
		VERTEX_ATTR_COLOR,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(vertex_t),
		(const GLvoid*) (offsetof(vertex_t, color))
	);

	glBindVertexArray(vao);
}

void update_graphics()
{
	glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(vao);

	glDrawArrays(
		GL_TRIANGLES,
		0,
		vertices_amount);

	glBindVertexArray(0);

}
