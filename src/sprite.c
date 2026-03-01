#include "sprite.h"
#include <stdlib.h>

sprite_t* create_sprite(mesh_t* mesh, texture_t* tex)
{
	sprite_t* sprite = malloc(sizeof(sprite_t));

	sprite->tex = tex;
	sprite->mesh = mesh;

	sprite->transform.pos.x = 0;
	sprite->transform.pos.y = 0;

	sprite->transform.scale.y = 1;
	sprite->transform.scale.y = 1;

	sprite->transform.rotation = 0.0;

	return sprite;
}

void set_sprite_transform(sprite_t* sprite, vec2_t pos, vec2_t scale, float rotation)
{
	sprite->transform.pos = pos;
	sprite->transform.scale = scale;
	sprite->transform.rotation = rotation;
}

void set_sprite_pos(sprite_t* sprite, vec2_t pos)
{
	sprite->transform.pos = pos;
}

