#include "texture.h"
#include "image.h"
#include <stdlib.h>

texture_t* create_texture(int width, int height, void* data)
{
	texture_t* tex = malloc(sizeof(texture_t));

	tex->width = width;
	tex->height = height;

	glGenTextures(1, &tex->id);
	glBindTexture(GL_TEXTURE_2D, tex->id);

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		width,
		height,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		data
	);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);

	return tex;
}

texture_t* create_texture_image(image_t* img)
{
	return create_texture(img->width, img->height, img->data);
}

texture_t* create_texture_atlas(atlas_t* atlas)
{
	return create_texture(atlas->width, atlas->height, atlas->data);
}
