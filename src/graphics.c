#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "graphics.h"
#include "shaders.h"
#include "camera.h"
#include "image.h"
#include "zmath.h"

// globals
const GLuint VERTEX_ATTR_POSITION = 0;
const GLuint VERTEX_ATTR_COLOR = 1;
const GLuint VERTEX_ATTR_TEXTURE = 2;
const GLuint VERTEX_ATTR_MODEL = 3;

// locals
static const uint64_t DEFAULT_SIZE = 100;

static GLuint shader_program;
static GLuint texture;

static GLint u_texture_location;

static GLuint vbo;
static GLuint vao;
static GLuint ebo;
static GLuint ibo;

static vertexUV_t* vertices;
static unsigned int* indices;
static vec2_t* positions;

static uint64_t vertices_amount = 0;
static uint64_t vertices_size = 0;

static uint64_t indices_amount = 0;
static uint64_t indices_size = 0;

static uint64_t positions_amount = 0;
static uint64_t positions_size = 0;

int add_vertex(vertexUV_t vertex)
{
	if (vertices_amount >= vertices_size)
		return 1;

	vertices[vertices_amount] = vertex;
	vertices_amount++;

	return 0;
}

int add_vertices(vertexUV_t* ivertices, uint64_t size)
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

void bind_texture(const char* path, GLuint program)
{
	int texture_width;
	int texture_height;
	load_png("assets/img/brotabro.png", &texture, &texture_width, &texture_height);

	u_texture_location = glGetUniformLocation(program, "uTexture");
	glUniform1i(u_texture_location, 0);
}

void init_shaders()
{
	GLuint vert_shader;
	GLuint frag_shader;

	create_shader("assets/shaders/vert/texture.glsl", GL_VERTEX_SHADER, &vert_shader);
	create_shader("assets/shaders/frag/texture.glsl", GL_FRAGMENT_SHADER, &frag_shader);

	GLuint shaders[] = {vert_shader, frag_shader};

	create_shader_program(&shader_program, shaders, 2);
}

void gen_buffers()
{
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glGenBuffers(1, &ibo);
}

void bind_buff_data()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices_amount * sizeof(vertexUV_t), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_amount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, ibo);
	glBufferData(GL_ARRAY_BUFFER, positions_amount * sizeof(vec2_t), positions, GL_DYNAMIC_DRAW);
}

void draw()
{
	vertices[0].position.x = 1.0; vertices[0].position.y = 0.0;
	vertices[0].texture.x = 1.0; vertices[0].texture.y = 1.0;

	vertices[1].position.x = 0.0; vertices[1].position.y = 1.0;
	vertices[1].texture.x = 0.0; vertices[1].texture.y = 0.0;


	vertices[2].position.x = 0.0; vertices[2].position.y = 0.0;
	vertices[2].texture.x = 0.0; vertices[2].texture.y = 1.0;

	vertices[3].position.x = 1.0; vertices[3].position.y = 1.0;
	vertices[3].texture.x = 1.0; vertices[3].texture.y = 0.0;

	vertices_amount = 4;

	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 0; indices[4] = 3; indices[5] = 1;

	indices_amount = 6;

	positions[0].x = 0.0; positions[0].y = 0.0;
	positions[1].x = 1.0; positions[1].y = 1.0;
	positions_amount = 2;
}

void attrib_pointers()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

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

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindBuffer(GL_ARRAY_BUFFER, ibo);

	glEnableVertexAttribArray(VERTEX_ATTR_MODEL);
	glVertexAttribPointer(VERTEX_ATTR_MODEL,
						  2,
						  GL_FLOAT,
						  GL_FALSE,
						  sizeof(vec2_t),
						  (const void*) 0);

	glVertexAttribDivisor(VERTEX_ATTR_MODEL, 1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void init_graphics()
{
	printf("GPU: %s\n", glGetString(GL_RENDERER));
	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Version: %s\n", glGetString(GL_VERSION));

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	vertices = malloc(sizeof(vertexUV_t) * DEFAULT_SIZE);
	positions = malloc(sizeof(vec2_t) * DEFAULT_SIZE);
	indices = malloc(sizeof(unsigned int) * DEFAULT_SIZE);

	vertices_size = DEFAULT_SIZE;
	positions_size = DEFAULT_SIZE;
	indices_size = DEFAULT_SIZE;

	draw();

	init_shaders();
	bind_texture("assets/img/brotabro.png", shader_program);

	init_camera();
	link_camera(shader_program);

	gen_buffers();

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	bind_buff_data();

	attrib_pointers();

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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

	glBindBuffer(GL_ARRAY_BUFFER, ibo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, positions_amount * sizeof(vec2_t), positions);

	glDrawElementsInstanced(GL_TRIANGLES, indices_amount, GL_UNSIGNED_INT, NULL, positions_amount);

	glBindVertexArray(0);
}
