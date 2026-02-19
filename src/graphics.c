#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "graphics.h"
#include "shaders.h"
#include "camera.h"
#include "image.h"

// globals
const GLuint VERTEX_ATTR_POSITION = 0;
const GLuint VERTEX_ATTR_COLOR = 1;
const GLuint VERTEX_ATTR_TEXTURE = 2;

// locals
static const uint64_t DEFAULT_VERTICES_SIZE = 100;

static GLuint shader_program;
static GLuint texture;

static GLint u_texture_location;

static GLuint vbo;
static GLuint vao;
static GLuint ebo;

static vertex_t* vertices;
static vertexUV_t* verticesUV;

static unsigned int* indices;
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

void draw_quad()
{
	vertex_t vs[] = {
		{
			.position = { .x = 1.0f, .y = 0.0f },
			.color    = { .r = 1.0f, .g = 0.0f, .b = 0.0f }
		},
		{
			.position = { .x = 0.0f, .y = 1.0f },
			.color    = { .r = 0.0f, .g = 1.0f, .b = 0.0f }
		},
		{
			.position = { .x = 0.0f, .y = 0.0f },
			.color    = { .r = 0.0f, .g = 0.0f, .b = 1.0f }
		},
		{
			.position = { .x = 1.0f, .y = 1.0f },
			.color    = { .r = 0.0f, .g = 0.0f, .b = 1.0f }
		},
	};

	add_vertices(vs, 4);
}

void draw_image(const char* path, GLuint program)
{
	int texture_width;
	int texture_height;
	load_png("assets/img/brotabro.png", &texture, &texture_width, &texture_height);

	u_texture_location = glGetUniformLocation(program, "uTexture");
	glUniform1i(u_texture_location, 0);
	
	verticesUV[0].position.x = 1.0; verticesUV[0].position.y = 0.0;
	verticesUV[0].texture.x = 1.0; verticesUV[0].texture.y = 1.0;

	verticesUV[1].position.x = 0.0; verticesUV[1].position.y = 1.0;
	verticesUV[1].texture.x = 0.0; verticesUV[1].texture.y = 0.0;


	verticesUV[2].position.x = 0.0; verticesUV[2].position.y = 0.0;
	verticesUV[2].texture.x = 0.0; verticesUV[2].texture.y = 1.0;

	verticesUV[3].position.x = 1.0; verticesUV[3].position.y = 1.0;
	verticesUV[3].texture.x = 1.0; verticesUV[3].texture.y = 0.0;

	vertices_amount = 4;
}

void attrib_vertexUV()
{
	glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
	glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);

	glVertexAttribPointer(
		VERTEX_ATTR_POSITION,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(vertexUV_t),
		(void*)offsetof(vertexUV_t, position)
	);

	glVertexAttribPointer(
		VERTEX_ATTR_TEXTURE,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(vertexUV_t),
		(void*)offsetof(vertexUV_t, texture)
	);
}

void attrib_vertex()
{
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
}

void init_graphics()
{
	printf("GPU: %s\n", glGetString(GL_RENDERER));
	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Version: %s\n", glGetString(GL_VERSION));

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLuint vert_shader;
	GLuint frag_shader;

	create_shader("assets/shaders/vert/texture.glsl", GL_VERTEX_SHADER, &vert_shader);
	create_shader("assets/shaders/frag/texture.glsl", GL_FRAGMENT_SHADER, &frag_shader);

	GLuint shaders[] = {vert_shader, frag_shader};

	create_shader_program(&shader_program, shaders, 2);

	// vertices = malloc(sizeof(vertex_t) * DEFAULT_VERTICES_SIZE);
	// vertices_size = DEFAULT_VERTICES_SIZE;

	verticesUV = malloc(sizeof(vertexUV_t) * DEFAULT_VERTICES_SIZE);
	vertices_size = DEFAULT_VERTICES_SIZE;

	init_camera();
	link_camera(shader_program);

	// draw_triangle();
	// draw_quad();
	draw_image("assets/img/brotabro.png", shader_program);

	// TODO
	indices = malloc(6 * sizeof(unsigned int));
	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 0; indices[4] = 3; indices[5] = 1;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(
		GL_ARRAY_BUFFER,
		//vertices_amount * sizeof(vertex_t),
		vertices_amount * sizeof(vertexUV_t),
		verticesUV,
		GL_STATIC_DRAW
	);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, indices, GL_STATIC_DRAW); 

	// attrib_vertex();
	attrib_vertexUV();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void update_graphics()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shader_program);
	glBindVertexArray(vao);

	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(u_texture_location, 0);

	update_camera();

	/*
	glDrawArrays(
		GL_TRIANGLES,
		0,
		vertices_amount); */

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);

}
