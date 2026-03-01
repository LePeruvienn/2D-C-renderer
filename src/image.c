#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "image.h"
#include <stdlib.h>

image_t* create_image(char* filepath)
{
	image_t* img = malloc(sizeof(image_t));

	img->filepath = filepath;
	img->data = NULL;
	img->channels = 0;
	img->width = 0;
	img->height = 0;
	img->is_loaded = false;

	return img;
}

void load_image(image_t* img)
{
	if (img->is_loaded)
	{
		return;
	}

	// cause opengl origin is at bottom left
	stbi_set_flip_vertically_on_load(1);

	// If force 4 channels to have RBGA
	img->data = stbi_load(img->filepath, &img->width, &img->height, &img->channels, STBI_rgb_alpha);

	img->is_loaded = true;
}

void free_image(image_t* img)
{
	if (img->data)
		stbi_image_free(img->data);

	free(img);
}
