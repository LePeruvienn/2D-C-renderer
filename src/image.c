#include "image.h"
#include "png.h"
#include <string.h>
#include <stdlib.h>

int load_png(char* path, GLuint* out, int* width, int* height)
{
	png_image image;
	memset(&image, 0, sizeof(image));

	image.version = PNG_IMAGE_VERSION;

	if (!png_image_begin_read_from_file(&image, path))
	{
		return 1;
	}

	png_bytep buffer = malloc(PNG_IMAGE_SIZE(image));

	if (!buffer)
	{
		png_image_free(&image);
		return 3;
	}

	image.format = PNG_FORMAT_RGBA;

	if (!png_image_finish_read(&image, NULL, buffer, 0, NULL))
	{
		png_image_free(&image);
		return 2;
	}

	*width = image.width;
	*height = image.height;

	GLuint texture;
	
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, *width, *height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);

	free(buffer);
	png_image_free(&image);

	*out = texture;

	return 0;
}

