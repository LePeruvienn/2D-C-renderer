#ifndef SPRITE_H
#define SPRITE_H

#include "zmath.h"
#include "texture.h"

typedef struct sprite
{
	vec2_t pos;
	vec2_t scale;
	texture_t* tex;

} sprite_t;


sprite_t* create_sprite(char* filepath);

#endif // SPRITE_H
