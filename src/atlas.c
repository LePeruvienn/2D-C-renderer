#include "atlas.h"
#include <stdlib.h>

atlas_t* create_atlas(int width, int height, int channels)
{
	atlas_t* atlas = malloc(sizeof(atlas_t));

	atlas->width = width;
	atlas->height = height;
	atlas->channels = channels;

	atlas->data = malloc(sizeof(unsigned char) * width * height * channels);

	for(unsigned int i = 0; i < width * height; i++)
	{
		atlas->data[i] = 0;
	}

	atlas->cursor_x = 0;
	atlas->cursor_y = 0;

	atlas->row_height = 0;

	return atlas;
}
void atlas_add_image(atlas_t* atlas, image_t* img)
{
	bool no_enough_space = (atlas->cursor_x + img->width > atlas->width &&
	                        atlas->cursor_y + img->height > atlas->height);

	if (img->is_loaded == false || no_enough_space )
	{
		return;
	}

	if (atlas->row_height == 0)
	{
		atlas->row_height = img->height;
	}

	if (img->height > atlas->row_height)
	{
		atlas->cursor_x = 0;
	}
}
