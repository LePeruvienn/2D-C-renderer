#ifndef ATLAS_H
#define ATLAS_H

#include "image.h"
#include "zmath.h"

typedef struct atlas
{
	int id;
	int width;
	int height;
	int channels;
	unsigned int cursor_x;
	unsigned int cursor_y;
	unsigned int row_height;
	unsigned char* data;
	bool is_empty;

} atlas_t;

typedef struct uv_rect
{
	vec2_t min;
	vec2_t max;

} uv_rect_t;

atlas_t* create_atlas(int width, int height, int channels);
void free_atlas(atlas_t* atlas);

void atlas_add_image(atlas_t* atlas, image_t* img, uv_rect_t* uv);

void atlas_write_image(atlas_t* atlas, char* filename);

#endif // ATLAS_H
