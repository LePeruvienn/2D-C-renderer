#ifndef SPRITE_H
#define SPRITE_H

#include "texture.h"
#include "transform.h"
#include "mesh.h"

typedef struct sprite
{
	transform_t transform;
	mesh_t* mesh;
	texture_t* tex;

} sprite_t;


sprite_t* create_sprite(mesh_t* mesh, texture_t* tex);
void set_sprite_transform(sprite_t* sprite, vec2_t pos, vec2_t scale, float rotation);
void set_sprite_pos(sprite_t* sprite, vec2_t pos);

#endif // SPRITE_H
