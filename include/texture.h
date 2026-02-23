#ifndef TEXTURE_H
#define TEXTURE_H

#include "image.h"
#include "glad/glad.h"
#include <stdbool.h>

typedef struct texture
{
	GLuint id;
	image_t* img;
	bool is_loaded;

} texture_t;


texture_t* create_texture(char* filepath);
void load_texture(texture_t* tex);

#endif // TEXTURE_H
