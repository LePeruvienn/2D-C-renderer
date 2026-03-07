#ifndef TEXTURE_H
#define TEXTURE_H

#include "image.h"
#include "atlas.h"
#include "glad/glad.h"
#include <stdbool.h>

typedef struct texture
{
	GLuint id;
	int width;
	int height;

} texture_t;


texture_t* create_texture(int width, int height, void* data);

texture_t* create_texture_image(image_t* img);
texture_t* create_texture_atlas(atlas_t* atlas);

#endif // TEXTURE_H
