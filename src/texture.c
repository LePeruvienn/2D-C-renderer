#include "texture.h"
#include <stdlib.h>

texture_t* create_texture(char* filepath)
{
	texture_t* tex = malloc(sizeof(texture_t));
	image_t* img = create_image(filepath);

	tex->id = 0;
	tex->img = img;
	tex->is_loaded = false;

	return tex;
}

void load_texture(texture_t* tex)
{
	glGenTextures(1, &tex->id);
	glBindTexture(GL_TEXTURE_2D, tex->id);

	image_t* img = tex->img;

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->width, img->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img->data);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);
}
