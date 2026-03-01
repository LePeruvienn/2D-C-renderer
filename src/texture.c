#include "texture.h"
#include "image.h"
#include <stdlib.h>

texture_t* create_texture(image_t* img)
{
	texture_t* tex = malloc(sizeof(texture_t));

	tex->width = img->width;
	tex->height = img->height;

	glGenTextures(1, &tex->id);
	glBindTexture(GL_TEXTURE_2D, tex->id);

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		img->width,
		img->height,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		img->data
	);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);

	return tex;
}
