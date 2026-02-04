#include <stdlib.h>
#include "zmath.h"

vec2_t* create_vec2(float x, float y)
{
	vec2_t* vec = malloc(sizeof(vec2_t));
	vec->x = x;
	vec->y = y;

	return vec;
}

color_t* create_color(float r, float g, float b)
{
	color_t* color = malloc(sizeof(color_t));
	color->r = r;
	color->g = g;
	color->b = b;

	return color;
}
