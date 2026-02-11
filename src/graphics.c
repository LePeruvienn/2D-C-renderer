#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "graphics.h"
#include "shaders.h"
#include "camera.h"

// globals
const GLuint VERTEX_ATTR_POSITION = 0;
const GLuint VERTEX_ATTR_COLOR = 1;

// locals
static const uint64_t DEFAULT_VERTICES_SIZE = 100;

static GLuint shader_program;

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
			.color    = { .r = 1.0f, .g = 0.0f, .b = 0.0f }
		},
		{
			.position = { .x = -1.0f, .y = -0.5f },
			.color    = { .r = 0.0f, .g = 1.0f, .b = 0.0f }
		},
		{
			.position = { .x = 1.0f, .y = -0.5f },
			.color    = { .r = 0.0f, .g = 0.0f, .b = 1.0f }
		}
	};

	add_vertices(vs, 3);
}

void init_graphics()
{
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Version: %s\n", glGetString(GL_VERSION));

	GLuint vert_shader;
	GLuint frag_shader;

	create_shader("shaders/vert/default.glsl", GL_VERTEX_SHADER, &vert_shader);
	create_shader("shaders/frag/default.glsl", GL_FRAGMENT_SHADER, &frag_shader);

	GLuint shaders[] = {vert_shader, frag_shader};

	create_shader_program(&shader_program, shaders, 2);

	vertices = malloc(sizeof(vertex_t) * DEFAULT_VERTICES_SIZE);
	vertices_size = DEFAULT_VERTICES_SIZE;

	init_camera();
	link_camera(shader_program);

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
	glEnableVertexAttribArray(VERTEX_ATTR_COLOR);

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
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(vertex_t),
		(void*)offsetof(vertex_t, color)
	);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void update_graphics()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shader_program);
	glBindVertexArray(vao);

	update_camera();

	glDrawArrays(
		GL_TRIANGLES,
		0,
		vertices_amount);

	glBindVertexArray(0);

}
