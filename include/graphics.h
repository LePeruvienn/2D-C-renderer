#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "zmath.h"
#include "glad/glad.h"

typedef vec2_t uv_t;

typedef struct vertex
{
	vec2_t position;
	color_t color;
	uv_t uv;

} vertex_t;

extern const GLuint VERTEX_ATTR_POSITION;
extern const GLuint VERTEX_ATTR_COLOR;

void init_graphics();
void update_graphics();

#endif // GRAPHICS_H
