#ifndef IMAGE_H
#define IMAGE_H

#include "glad/glad.h"
#include <stdbool.h>

typedef struct image
{
	char* filepath;
	unsigned char* data;
	int channels;
	int width;
	int height;
	bool is_loaded;

} image_t;

image_t* create_image(char* filepath);
void load_image(image_t* img);
void free_image(image_t* img);

#endif // IMAGE_H
