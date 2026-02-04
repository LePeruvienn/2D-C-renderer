#include "graphics.h"

static GLuint vbo;
static GLuint vao;

void init_graphics()
{
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
}

void update_graphics()
{
	glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}
