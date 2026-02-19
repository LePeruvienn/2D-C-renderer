#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "zmath.h"
#include "glad/glad.h"

typedef struct vertex {
	vec2_t position;
	color_t color;
} vertex_t;

typedef struct vertexUV {
	vec2_t position;
	vec2_t texture;
} vertexUV_t;

extern const GLuint VERTEX_ATTR_POSITION;
extern const GLuint VERTEX_ATTR_COLOR;

void init_graphics();
void update_graphics();

#endif // GRAPHICS_H
