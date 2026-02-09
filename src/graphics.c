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

static vertex_t* vertices;
static uint64_t vertices_amount = 0;
static uint64_t vertices_size = 0;

int add_vertex(vertex_t vertex)
{
	if (vertices_amount >= vertices_size)
		return 1;

	vertices[vertices_amount] = vertex;
	vertices_amount++;

	return 0;
}

int add_vertices(vertex_t* ivertices, uint64_t size)
{
	if (vertices_amount + size > vertices_size)
		return 1;

	for (size_t i = 0; i < size; i++)
	{
		vertices[i + vertices_amount] = ivertices[i];
	}

	vertices_amount += size;
	
	return 0;
}

void draw_triangle()
{
	vertex_t vs[] = {
		{
			.position = { .x = 0.0f, .y = 1.0f },
			.color    = { .r = 1.0f, .g = 1.0f, .b = 1.0f }
		},
		{
			.position = { .x = -1.0f, .y = 0.0f },
			.color    = { .r = 1.0f, .g = 1.0f, .b = 1.0f }
		},
		{
			.position = { .x = 1.0f, .y = 0.0f },
			.color    = { .r = 1.0f, .g = 1.0f, .b = 1.0f }
		}
	};

	add_vertices(vs, 3);
}

void load_shader()
{

}

void init_graphics()
{
	vertices = malloc(sizeof(vertex_t) * DEFAULT_VERTICES_SIZE);
	vertices_size = DEFAULT_VERTICES_SIZE;

	draw_triangle();

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(
		GL_ARRAY_BUFFER,
		vertices_amount * sizeof(vertex_t),
		vertices,
		GL_STATIC_DRAW
	);

	glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
	glVertexAttribPointer(
		VERTEX_ATTR_POSITION,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(vertex_t),
		(void*)offsetof(vertex_t, position)
	);

	glEnableVertexAttribArray(VERTEX_ATTR_COLOR);
	glVertexAttribPointer(
		VERTEX_ATTR_COLOR,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(vertex_t),
		(void*)offsetof(vertex_t, color)
	);

	glBindVertexArray(0);
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
