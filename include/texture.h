#ifndef TEXTURE_H
#define TEXTURE_H

#include "image.h"
#include "glad/glad.h"
#include <stdbool.h>

typedef struct texture
{
	GLuint id;
	int width;
	int height;

} texture_t;


texture_t* create_texture(image_t* img);

#endif // TEXTURE_H
