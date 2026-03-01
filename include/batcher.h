#ifndef BATCHER_H
#define BATCHER_H

#include "sprite.h"

void init_draw(GLuint shader);
void begin_draw();
void draw(sprite_t* sprite);
void flush_draw();

#endif // BATCHER_H
