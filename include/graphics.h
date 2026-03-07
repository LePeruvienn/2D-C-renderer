#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "zmath.h"
#include "glad/glad.h"

typedef vec2_t vertex_t;
typedef vec2_t uv_t;

typedef struct vertexUV
{
	vec2_t position;
	vec2_t texture;

} vertexUV_t;

extern const GLuint VERTEX_ATTR_POSITION;
extern const GLuint VERTEX_ATTR_COLOR;

void init_graphics();
void update_graphics();

#endif // GRAPHICS_H
