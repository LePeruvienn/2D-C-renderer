#ifndef MATH_H
#define MATH_H

typedef struct vec2 {
	float x;
	float y;
} vec2_t;

typedef struct color {
	float r;
	float g;
	float b;
} color_t;

vec2_t* create_vec2(float x, float y);
color_t* create_color(float r, float g, float b);

#endif // MATH_H
