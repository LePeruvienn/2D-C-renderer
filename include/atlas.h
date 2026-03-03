#ifndef ATLAS_H
#define ATLAS_H

#include "image.h"

typedef struct atlas {

	int id;
	int width;
	int height;
	int channels;
	unsigned int cursor_x;
	unsigned int cursor_y;
	unsigned int row_height;
	unsigned char* data;

} atlas_t;

atlas_t* create_atlas(int width, int height, int channels);
void atlas_add_image(atlas_t* atlas, image_t* img);

#endif // ATLAS_H
