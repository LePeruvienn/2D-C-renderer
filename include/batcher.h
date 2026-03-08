#ifndef BATCHER_H
#define BATCHER_H

#include "sprite.h"

typedef struct sprite_instance
{
	uv_rect_t uv;
	transform_t trans;

} sprite_instance_t;

void init_draw(GLuint shader);
void begin_draw();
void draw(sprite_t* sprite);
void flush_draw();

#endif // BATCHER_H
