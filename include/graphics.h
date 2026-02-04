#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <zmath.h>
#include "glad/glad.h"

typedef struct vertex {
	vec2_t position;
	color_t color;
} vertex_t;

void update_graphics();

#endif // GRAPHICS_H
