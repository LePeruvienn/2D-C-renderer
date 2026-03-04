#include "atlas.h"
#include <stdlib.h>
#include <string.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

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

	atlas->is_empty = true;

	return atlas;
}

void free_atlas(atlas_t* atlas)
{
	free(atlas->data);
	free(atlas);
}

void atlas_add_image(atlas_t* atlas, image_t* img)
{
	bool not_same_channels = atlas->channels != img->channels;

	bool not_enough_width = (atlas->cursor_x + img->width > atlas->width) || atlas->row_height < img->height;
	bool not_enough_height = atlas->row_height + atlas->cursor_y + img->height > atlas->height;

	bool not_enough_space = not_enough_width && not_enough_height;

	if (!atlas->is_empty && (!img->is_loaded || not_same_channels || not_enough_space))
	{
		printf("RETURN");
		return;
	}

	if (!atlas->is_empty && not_enough_width)
	{
		atlas->cursor_x = 0;
		atlas->cursor_y += atlas->row_height;
		atlas->row_height = img->height;
	}

	int channels = atlas->channels;
	unsigned int cursor_x = atlas->cursor_x;
	unsigned int cursor_y = atlas->cursor_y;

	for (unsigned int img_y = 0; img_y < img->height; img_y++)
	{
		unsigned int atlas_offset = ((cursor_y + img_y) * atlas->width * channels) + (cursor_x * channels);
		unsigned int img_offset   = img_y * img->width * channels;

		memcpy(atlas->data + atlas_offset, img->data + img_offset, img->width * channels);
	}

	if (atlas->is_empty)
	{
		atlas->row_height = img->height;
		atlas->is_empty = false;
	}
}

void atlas_write_image(atlas_t* atlas, char* filename)
{
	stbi_write_png(
		filename,
		atlas->width,
		atlas->height,
		atlas->channels,
		atlas->data,
		atlas->width * atlas->channels
	);
}
