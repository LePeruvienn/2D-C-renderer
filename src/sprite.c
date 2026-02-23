#include "sprite.h"
#include <stdlib.h>

sprite_t* create_sprite(char* filepath)
{
	sprite_t* sprite = malloc(sizeof(sprite_t));
	sprite->tex = create_texture(filepath);

	sprite->pos.x = 0;
	sprite->pos.y = 0;

	sprite->scale.x = 0;
	sprite->scale.y = 0;

	return sprite;
}
